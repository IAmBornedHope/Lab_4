#pragma once
#include <concepts>
#include <functional>
#include "../lazy_sequence/Cardinal.hpp"
#include "IGenerator.hpp"


template<typename Container, typename T>
concept Recurrentable = requires(Container& container, T value, size_t index) {
    { container.get_length() } -> std::convertible_to<size_t>;
    { container[index] } -> std::convertible_to<T>;
    { container.append(value) };
};

template<typename T, template<typename> class Container>
requires Recurrentable<Container<T>, T>
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

    std::shared_ptr<IGenerator<T>> clone() const override {
        return std::make_shared<RecurrentGenerator<T, Container>>(function_, cache_);
    }
};