#pragma once
#include "IGenerator.hpp"
#include "libs/Lab_3/exceptions/Exceptions.hpp"

template<typename Container, typename T>
concept Indexable = requires(Container& container, size_t index) {
    { container.get_length() } -> std::convertible_to<size_t>;
    { container[index] } -> std::convertible_to<T>;
};

template<typename T, template<typename> class Container>
requires Indexable<Container<T>, T>
class ContainerGenerator: public IGenerator<T> {
private:
    Container<T> items_;
    size_t current_;

public:
    ContainerGenerator(const Container<T>& container) : items_{container}, current_{0} {}
    
    bool has_next() const override {
        return current_ < items_.get_length();
    }

    T get_next() override {
        if (!has_next()) {
            throw IndexOutOfRangeException(current_, items_.get_length());
        }
        return items_[current_++];
    }

    size_t get_position() const {
        return current_;
    }

    Cardinal size() const override {
        return Cardinal(items_.get_length());
    }

};
