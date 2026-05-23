#pragma once
#include <functional>
#include "../lazy_sequence/Cardinal.hpp"
#include "IGenerator.hpp"

template<typename T, template<typename> class Container>
class RecurrentGenerator: public IGenerator<T> {
private:
    std::function<T(const Container<T>&)> function_;
    Container<T> cache_;

public:
    RecurrentGenerator(std::function<T(const Container<T>&)> function, const Container<T>& cache_container)
        : function_{function}, cache_{cache_container} {}

    bool has_next() const override {
        return true;
    }

    T get_next() override {
        T new_value = function_(cache_);
        cache_.append(new_value);

        return new_value;
    }

    size_t get_position() const {
        return cache_.get_length();
    }

    Cardinal size() const override {
        return Cardinal::aleph_null();
    }
};