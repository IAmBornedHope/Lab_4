#pragma once
#include "BinaryHeap.hpp"
#include "../streams/LazyInputStream.hpp"
#include "../streams/SequenceOutputStream.hpp"

template<typename T, typename InputType, typename OutType>
void sort_stream(InputType& input_stream, OutType& output_stream, SortingOrder order) {
    BinaryHeap<T> heap(order);

    while (input_stream.has_next()) {
        T value = input_stream.read();
        heap.push(value);
    }

    while (!heap.is_empty()) {
        T value = heap.extract_top();
        output_stream.write(value);
    }
}