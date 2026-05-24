#pragma once
#include <functional>
#include <memory>
#include "IGenerator.hpp"

template<typename T>
class FilterGenerator : public IGenerator<T> {
private:
    std::shared_ptr<IGenerator<T>> base_;
    std::function<bool(T)> predicate_;
    mutable bool is_found_ = false;;
    mutable T filtered_value_;
    
    void check_found() const {
        if (is_found_) {
            return;
        }

        while (base_->has_next()) {
            T value = base_->get_next();
            if (predicate_(value)) {
                is_found_ = true;
                filtered_value_ = value;
                return;
            }
        }
    }

public:
    FilterGenerator(std::shared_ptr<IGenerator<T>> base, std::function<bool(T)> predicate)
        : base_{base}, predicate_{predicate} {}

    bool has_next() const override {
        check_found();
        return is_found_;
    }

    T get_next() override {
        check_found();
        if (!is_found_) {
            throw IndexOutOfRangeException("Читать нечего");
        }
        is_found_ = false;
        return filtered_value_;
    }

    Cardinal size() const override {
        Cardinal base_size = base_->size();
        if (base_size.is_infinite()) {
            return Cardinal::aleph_null();
        }

        auto temp = this->clone();
        size_t count = 0;
        while (temp->has_next()) {
            temp->get_next();
            ++count;
        }
        return Cardinal(count);
    }

    std::shared_ptr<IGenerator<T>> clone() const override {
        return std::make_shared<FilterGenerator<T>>(base_->clone(), predicate_);
    }
    

};