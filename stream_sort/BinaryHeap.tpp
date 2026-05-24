#include "BinaryHeap.hpp"

template<typename T>
void swap(T& first, T& second) {
    T temp = first;
    first = second;
    second = temp;
}



template<typename T>
BinaryHeap<T>::BinaryHeap(SortingOrder order) : order_{order} {}


template<typename T>
bool BinaryHeap<T>::comparator(const T& first, const T& second) const {
    if (order_ == SortingOrder::ascending) {
        return first < second;
    }
    return first > second;
}

template<typename T>
void BinaryHeap<T>::heapify_up(size_t index) {
    while (index > 0) {
        size_t parent_index = parent(index);

        if (comparator(heap_[index], heap_[parent_index])) {
            swap(heap_[index], heap_[parent_index]);
            index = parent_index;
        }
        else {
            break;
        }
    }
}

template<typename T>
void BinaryHeap<T>::heapify_down(size_t index) {
    size_t heap_size = heap_.get_length();

    size_t left = left_child(index);
    size_t best = index;
    size_t right = right_child(index);

    if (left < heap_size && comparator(heap_[left], heap_[best])) {
        best = left;
    }

    if (right < heap_size && comparator(heap_[right], heap_[best])) {
        best = right;
    }

    if (best != index) {
        swap(heap_[index], heap_[best]);
        heapify_down(best);
    }
}

template<typename T>
bool BinaryHeap<T>::is_empty() const {
    return heap_.get_length() == 0;
}

template<typename T>
size_t BinaryHeap<T>::size() const {
    return heap_.get_length();
}

template<typename T>
T BinaryHeap<T>::top() const {
    if (is_empty()) {
        throw EmptyListException();
    }
    return heap_[0];
}

template<typename T>
void BinaryHeap<T>::push(const T& value) {
    heap_.append(value);
    heapify_up(heap_.get_length() - 1);
}

template<typename T>
T BinaryHeap<T>::extract_top() {
    if (is_empty()) {
        throw EmptyListException();
    }
    size_t heap_size = heap_.get_length();
    T root = heap_[0];

    heap_[0] = heap_[heap_size - 1];
    heap_.pop_back();

    heapify_down(0);
    return root;
}

template<typename T>
void BinaryHeap<T>::clear() {
    heap_ = MutableArraySequence<T>();
}