#pragma once
#include <memory>

template<typename T, template<typename> class Container>
class LazySequence;

template<typename T, template<typename> class Container>
class LazyIterator {
private:
    LazySequence<T, Container>* sequence_;
    size_t current_;
public:
    LazyIterator(LazySequence<T, Container>* sequence, size_t current) : sequence_{sequence}, current_{current} {}

    T operator*() const {
        return sequence_->get(Cardinal(current_));
    }

    LazyIterator& operator++() {
        ++current_;
        return *this;
    }

    bool operator!=(const LazyIterator& iterator) const {
        return current_ != iterator.current_;
    }

    bool operator==(const LazyIterator& iterator) const {
        return current_ == iterator.current_;
    }
};

