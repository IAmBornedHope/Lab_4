#pragma once
#include "../libs/Lab_3/array_sequence/MutableArraySequence.hpp"

enum class SortingOrder {
    ascending, // min-heap, возрастание, минимальный поднимаем наверх
    descending // max-heap, убывание, максимальный наверх
};

template<typename T>
class BinaryHeap {
private:
    MutableArraySequence<T> heap_;
    SortingOrder order_ = SortingOrder::descending;

    size_t parent(size_t index) const { return (index - 1) / 2; }
    size_t left_child(size_t index) const { return (index * 2 + 1); }
    size_t right_child(size_t index) const { return (index * 2 + 2); }

    bool comparator(const T& first, const T& second) const;

    void heapify_up(size_t index);
    void heapify_down(size_t index);

public:
    BinaryHeap();
    BinaryHeap(SortingOrder order);

    bool is_empty() const;
    size_t size() const;

    T top() const;
    void push(const T& value);

    T extract_top();
    void clear();
};

#include "BinaryHeap.tpp"