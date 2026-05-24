#pragma once
#include <memory>
#include "IGenerator.hpp"

template<typename T>
class SkipGenerator: public IGenerator<T> {
private:
    std::shared_ptr<IGenerator<T>> base_;
    size_t count_;
    mutable bool is_skipped_ = false;

    void check_skip() const {
        if (is_skipped_) {
            return;
        }
        for (size_t index = 0; index < count_; ++index) {
            if(!base_->has_next()) {
                break;
            }
            base_->get_next();
        }
        is_skipped_ = true; 
    }

public:
    SkipGenerator(std::shared_ptr<IGenerator<T>> base, size_t count)
        : base_{base}, count_(count) {}

    bool has_next() const override {
        check_skip();
        return base_->has_next();
    }

    T get_next() override {
        check_skip();
        if (!base_->has_next()) {
            throw IndexOutOfRangeException("SkipGenerator: Нет след элемента");
        }
        return base_->get_next();
    }

    Cardinal size() const override {
        Cardinal base_size = base_->size();
        if (base_size.is_infinite()) {
            return Cardinal::aleph_null();
        }
        if (base_size.get_size() <= count_) {
            return Cardinal(0);
        }
        return Cardinal(base_size.get_size() - count_);
    }

    std::shared_ptr<IGenerator<T>> clone() const override {
        return std::make_shared<SkipGenerator<T>>(base_->clone(), count_);
    }

};
