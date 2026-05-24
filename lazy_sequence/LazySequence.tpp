#include "LazySequence.hpp"
#include "../libs/Lab_3/array_sequence/MutableArraySequence.hpp"
#include "../generators/RecurrentGenerator.hpp"
#include "../generators/ContainerGenerator.hpp"
#include "../generators/MapGenerator.hpp"
#include "../generators/ConcatGenerator.hpp"
#include "../generators/FilterGenerator.hpp"
#include "../generators/SkipGenerator.hpp"
#include "../generators/TakeGenerator.hpp"

template<typename T, template<typename> class Container>
void LazySequence<T, Container>::check_cached(Cardinal index) {
    if (index.is_infinite()) {
        throw IndexOutOfRangeException("Нельзя обратиться по бесконечному индексу");
    }
    size_t num_index = index.get_size();
    if (num_index < cache_.get_length()) {
        return;
    }

    if (!generator_) {
        throw InvalidArgumentException("Нет генератора");
    }

    while (cache_.get_length() <= num_index) {
        if (!generator_->has_next()) {
            generator_ = nullptr;
            break;
        }
        cache_.append(generator_->get_next());
    }
}

template<typename T, template<typename> class Container>
LazySequence<T, Container>::LazySequence() : cache_{}, generator_{nullptr} {}

template<typename T, template<typename> class Container>
LazySequence<T, Container>::LazySequence(T* items, size_t count) : cache_{}, generator_{nullptr} {
    Container<T> temp(items, count);
    generator_ = std::make_shared<ContainerGenerator<T, Container>>(temp);
}

template<typename T, template<typename> class Container>
LazySequence<T, Container>::LazySequence(const Container<T>& cache) : cache_{cache}, generator_{nullptr} {}

template<typename T, template<typename> class Container>
LazySequence<T, Container>::LazySequence(const Container<T>& cache, std::shared_ptr<IGenerator<T>> generator)
    : cache_{cache}, generator_{generator} {}

template<typename T, template<typename> class Container>
LazySequence<T, Container>::LazySequence(const LazySequence<T, Container>& lazy_sequence) : cache_{lazy_sequence.cache_} {
    if (lazy_sequence.generator_) {
        generator_ = lazy_sequence.generator_->clone();
    }
}

template<typename T, template<typename> class Container>
LazySequence<T, Container>::LazySequence(std::shared_ptr<IGenerator<T>> generator)
    : cache_{}, generator_{generator} {
}

template<typename T, template<typename> class Container>
LazySequence<T, Container>& LazySequence<T, Container>::operator=(const LazySequence& lazy_sequence) {
    if (this != &lazy_sequence) {
        cache_ = lazy_sequence.cache_;
        if (lazy_sequence.generator_) {
            generator_ = lazy_sequence.generator_->clone();
        }
        else {
            generator_ = nullptr;
        }
    }
    return *this;
}



template<typename T, template<typename> class Container>
T LazySequence<T, Container>::get(Cardinal index) {
    check_cached(index);
    return cache_[index.get_size()];
}

template<typename T, template<typename> class Container>
Container<T> LazySequence<T, Container>::get_cache() const {
    return cache_;
}

template<typename T, template<typename> class Container>
T LazySequence<T, Container>::get_first() {
    return get(Cardinal(0));
}

template<typename T, template<typename> class Container>
Cardinal LazySequence<T, Container>::get_length() const {
    if (generator_) {
        return generator_->size();
    }
    return Cardinal(cache_.get_length());
}

template<typename T, template<typename> class Container>
T LazySequence<T, Container>::get_last() {
    Cardinal length = get_length();
    if (length.is_infinite()) {
        throw IndexOutOfRangeException("У бесконечной последовательности нет последнего элемента");
    }

    if (generator_) {
        while (generator_->has_next()) {
            cache_.append(generator_->get_next());
        }
        generator_ = nullptr;
    }
    if (cache_.get_length() == 0) {
        throw EmptyListException();
    }

    return cache_[cache_.get_length() - 1];
}

template<typename T, template<typename> class Container>
size_t LazySequence<T, Container>::get_materialized_count() const {
    return cache_.get_length();
}

template<typename T, template<typename> class Container>
auto LazySequence<T, Container>::append(T item) const {
    Container<T> new_elem;
    new_elem.append(item);

    std::shared_ptr<IGenerator<T>> base_generator;

    auto append_generator = std::make_shared<ContainerGenerator<T, Container>>(new_elem);
    if (generator_) {
        base_generator = generator_->clone();
    }
    else {
        base_generator = std::make_shared<ContainerGenerator<T, Container>>(cache_);
    }

    auto result_generator = std::make_shared<ConcatGenerator<T>>(base_generator, append_generator);
    return std::make_shared<LazySequence<T, Container>>(Container<T>(), result_generator);
}

template<typename T, template<typename> class Container>
auto LazySequence<T, Container>::prepend(T item) const {
    Container<T> new_elem;
    new_elem.append(item);

    std::shared_ptr<IGenerator<T>> base_generator;

    auto prepend_generator = std::make_shared<ContainerGenerator<T, Container>>(new_elem);
    if (generator_) {
        base_generator = generator_->clone();
    }
    else {
        base_generator = std::make_shared<ContainerGenerator<T, Container>>(cache_);
    }

    auto result_generator = std::make_shared<ConcatGenerator<T>>(prepend_generator, base_generator);
    return std::make_shared<LazySequence<T, Container>>(Container<T>(), result_generator);
}

template<typename T, template<typename> class Container>
auto LazySequence<T, Container>::insert_at(T item, size_t index) const {
    auto before_target = take(index);
    Container<T> new_elem;
    new_elem.append(item);

    auto insert_sequence = std::make_shared<LazySequence<T, Container>>(new_elem);

    auto after_target = skip(index);
    return before_target->concat(insert_sequence)->concat(after_target);

}

template<typename T, template<typename> class Container>
auto LazySequence<T, Container>::concat(std::shared_ptr<LazySequence<T, Container>> lazy_sequence) const {
    std::shared_ptr<IGenerator<T>> first_generator;
    std::shared_ptr<IGenerator<T>> second_generator;

    if (generator_) {
        first_generator = generator_->clone();
    }
    else {
        first_generator = std::make_shared<ContainerGenerator<T, Container>>(cache_);
    }

    if (lazy_sequence->generator_) {
        second_generator = lazy_sequence->generator_->clone();
    }
    else {
        second_generator = std::make_shared<ContainerGenerator<T, Container>>(lazy_sequence->cache_);
    }

    auto result_generator = std::make_shared<ConcatGenerator<T>>(first_generator, second_generator);
    return std::make_shared<LazySequence<T, Container>>(Container<T>(), result_generator);

}

template<typename T, template<typename> class Container>
auto LazySequence<T, Container>::get_subsequence(size_t start_index, size_t end_index) const {
    if (start_index > end_index) {
        throw IndexOutOfRangeException("Начальный индекс больше конечного");
    }
    size_t count = end_index - start_index + 1;
    auto skipped = skip(start_index);
    return skipped->take(count);
}

template<typename T, template<typename> class Container>
template<typename U>
auto LazySequence<T, Container>::map(std::function<U(T)> function) const {
    std::shared_ptr<IGenerator<T>> base_generator;
    if (generator_) {
        base_generator = generator_->clone();
    }
    else {
        base_generator = std::make_shared<ContainerGenerator<T, Container>>(cache_);
    }

    auto result_generator = std::make_shared<MapGenerator<T, U>>(base_generator, function);
    return std::make_shared<LazySequence<U, Container>>(Container<U>(), result_generator);

}

template<typename T, template<typename> class Container>
auto LazySequence<T, Container>::where(std::function<bool(T)> predicate) const {
    std::shared_ptr<IGenerator<T>> base_generator;
    if (generator_) {
        base_generator = generator_->clone();
    }
    else {
        base_generator = std::make_shared<ContainerGenerator<T, Container>>(cache_);
    }

    auto result_generator = std::make_shared<FilterGenerator<T>>(base_generator, predicate);
    return std::make_shared<LazySequence<T, Container>>(Container<T>(), result_generator);
  
}

template<typename T, template<typename> class Container>
auto LazySequence<T, Container>::skip(size_t count) const {
    std::shared_ptr<IGenerator<T>> base_generator;
    if (generator_) {
        base_generator = generator_->clone();
    }
    else {
        base_generator = std::make_shared<ContainerGenerator<T, Container>>(cache_);
    }

    auto result_generator = std::make_shared<SkipGenerator<T>>(base_generator, count);
    return std::make_shared<LazySequence<T, Container>>(Container<T>(), result_generator);
     
}

template<typename T, template<typename> class Container>
auto LazySequence<T, Container>::take(size_t count) const {
    std::shared_ptr<IGenerator<T>> base_generator;
    if (generator_) {
        base_generator = generator_->clone();
    }
    else {
        base_generator = std::make_shared<ContainerGenerator<T, Container>>(cache_);
    }

    auto result_generator = std::make_shared<TakeGenerator<T>>(base_generator, count);
    return std::make_shared<LazySequence<T, Container>>(Container<T>(), result_generator);
     
}

template<typename T, template<typename> class Container>
LazyIterator<T, Container> LazySequence<T, Container>::begin() {
    return LazyIterator<T, Container>(this, 0);
}

template<typename T, template<typename> class Container>
LazyIterator<T, Container> LazySequence<T, Container>::end() {
    Cardinal length = get_length();
    if (length.is_infinite()) {
        throw IndexOutOfRangeException("У итератора нет конца в бесконечном случве");
    }
    return LazyIterator<T, Container>(this, length.get_size());
}

