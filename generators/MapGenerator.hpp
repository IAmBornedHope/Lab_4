#pragma once
#include <functional>
#include <memory>
#include "IGenerator.hpp"

template<typename T, typename U>
class MapGenerator : public IGenerator<U> {
private:
    std::shared_ptr<IGenerator<T>> base_;
    std::function<U(T)> mapper_;

public:
    MapGenerator(std::shared_ptr<IGenerator<T>> base, std::function<U(T)> mapper)
        : base_{base}, mapper_{mapper} {}

    bool has_next() const override {
        return base_->has_next();
    }

    U get_next() override {
        return mapper_(base_->get_next());
    }

    Cardinal size() const override {
        return base_->size();
    }
};
