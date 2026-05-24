#pragma once
#include "OutputStream.hpp"
#include "../libs/Lab_3/exceptions/Exceptions.hpp"
#include "../lazy_sequence/LazySequence.hpp"

template<typename T>
class SequenceOutputStream: public OutputStream<T> {
private:
    std::shared_ptr<Sequence<T>> sequence_;

public:
    SequenceOutputStream(std::shared_ptr<Sequence<T>> sequence) : sequence_{sequence} {}

    void write(const T& value) override {
        sequence_->append(value);
    }

};