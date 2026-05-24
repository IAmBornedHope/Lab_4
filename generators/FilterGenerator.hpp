#pragma once
#include <functional>
#include <memory>
#include "IGenerator.hpp"

template<typename T>
class FilterGenerator : public IGenerator<T> {
private:
    std::shared_ptr<IGenerator<T>> base_;
    std::function<bool(T)> predicate_;

public:
    FilterGenerator(std::shared_ptr<IGenerator<T>> base, std::function<bool(T)> predicate)
        : base_{base}, predicate_{predicate} {}

    bool has_next() const override {
        return base_->has_next();
    }

    T get_next() override {
        T value;
        while (true) {
            if (!base_->has_next()) {
                throw IndexOutOfRangeException("FilterGenerator: Поток пуст.");
            }
            value = base_->get_next();
            if (predicate_(value)) {
                return value;
            }
        }
    }

    Cardinal size() const override {
        Cardinal base_size = base_->size();
        if (base_size.is_infinite()) {
            return Cardinal::aleph_null();
        }
        return base_size;
    }

    std::shared_ptr<IGenerator<T>> clone() const override {
        return std::make_shared<FilterGenerator<T>>(base_->clone(), predicate_);
    }
    

};