#pragma once
#include <functional>
#include <memory>
#include "IGenerator.hpp"

template<typename T>
class ConcatGenerator : public IGenerator<T> {
private:
    std::shared_ptr<IGenerator<T>> first_;
    std::shared_ptr<IGenerator<T>> second_;

public:
    ConcatGenerator(std::shared_ptr<IGenerator<T>> first, std::shared_ptr<IGenerator<T>> second)
        : first_{first}, second_{second} {}

    bool has_next() const override {
        return (first_ && first_->has_next()) || (second_ && second_->has_next());
    }

    T get_next() override {
        if (first_ && first_->has_next()) {
            return first_->get_next();
        }
        if (second_ && second_->has_next()) {
            return second_->get_next();
        }
        throw IndexOutOfRangeException("Нечего конкатенировать");

    }

    Cardinal size() const override {
        Cardinal size_1(0);
        Cardinal size_2(0);
        if (first_) {
            size_1 = first_->size();
        }
        if (second_) {
            size_2 = second_->size();
        }

        if (size_1.is_infinite() || size_2.is_infinite()) {
            return Cardinal::aleph_null();
        }

        return Cardinal(size_1.get_size() + size_2.get_size());
    }
    

};