#pragma once
#include <memory>
#include "IGenerator.hpp"

template<typename T>
class TakeGenerator: public IGenerator<T> {
private:
    std::shared_ptr<IGenerator<T>> base_;
    size_t count_;
    mutable size_t taken_count_ = 0;
    mutable bool is_taken_ = false;

    void check_take() const {
        if (is_taken_) {
            return;
        }
        if (taken_count_ >= count_) {
            is_taken_ = true;
        }
    }

public:
    TakeGenerator(std::shared_ptr<IGenerator<T>> base, size_t count)
        : base_{base}, count_(count) {}

    bool has_next() const override {
        check_take();
        if (is_taken_) {
            return false;
        }
        return base_->has_next();
    }

    T get_next() override {
        check_take();
        if (!base_->has_next()) {
            throw IndexOutOfRangeException("TakeGenerator: Нет след элемента");
        }
        T value = base_->get_next();
        ++taken_count_;

        if (taken_count_ >= count_) {
            is_taken_ = true;
        }
        return value;
    }

    Cardinal size() const override {
        Cardinal base_size = base_->size();
        if (base_size.is_infinite()) {
            return Cardinal(count_);
        }
        if (base_size.get_size() < count_) {
            return base_size;
        }
        return Cardinal(count_);
    }

    std::shared_ptr<IGenerator<T>> clone() const override {
        return std::make_shared<TakeGenerator<T>>(base_->clone(), count_);
    }

};
