#pragma once
#include "../lazy_sequence/Cardinal.hpp"

template<class T>
class IGenerator {
public:
    virtual ~IGenerator() = default;
    virtual bool has_next() const = 0;
    virtual T get_next() = 0;
    virtual Cardinal size() const = 0;

    Option<T> try_get_next() {
        if (has_next()) {
            return Option<T>(get_next());
        }
        return Option<T>();
    }

    virtual std::shared_ptr<IGenerator<T>> clone() const = 0;

};