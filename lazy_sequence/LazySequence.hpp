#pragma once
#include <memory>
#include <functional>
#include "../libs/Lab_3/exceptions/Exceptions.hpp"
#include "../generators/IGenerator.hpp"
#include "Cardinal.hpp"
#include "LazySequenceIterator.hpp"

template<typename T, template<typename> class Container>
class LazySequence {
private:
    Container<T> cache_;
    std::shared_ptr<IGenerator<T>> generator_;

    void check_cached(Cardinal index);
public:
    LazySequence();
    LazySequence(T* items, size_t count);
    LazySequence(const Container<T>& cache);
    LazySequence(const Container<T>& cache, std::shared_ptr<IGenerator<T>> generator);
    LazySequence(const LazySequence<T, Container>& lazy_sequence);
    LazySequence(std::shared_ptr<IGenerator<T>> generator);

    LazySequence<T, Container>& operator=(const LazySequence<T, Container>& lazy_sequence);

    T get_first();
    T get_last();
    T get(Cardinal index);

    Cardinal get_length() const;;
    size_t get_materialized_count() const;
    
    Container<T> get_cache() const;

    auto append(T item) const;
    auto prepend(T item) const;
    auto insert_at(T item, size_t index) const;

    template<typename U>
    auto map(std::function<U(T)> function) const;
    auto where(std::function<bool(T)> predicate) const;
    auto skip(size_t count) const;
    auto take(size_t count) const;
    auto concat(std::shared_ptr<LazySequence<T, Container>> lazy_sequence) const;
    auto get_subsequence(size_t start_index, size_t end_index) const;

    LazyIterator<T, Container> begin();
    LazyIterator<T, Container> end();


};

#include "LazySequence.tpp"