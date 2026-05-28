#pragma once
#include "InputStream.hpp"
#include "../libs/Lab_3/sequence/Sequence.hpp"

template<typename T>
class SequenceInputStream: public InputStream<T> {
private:
    std::shared_ptr<Sequence<T>> sequence_;
    size_t current_ = 0;

public:
    SequenceInputStream(std::shared_ptr<Sequence<T>> sequence) : sequence_{sequence} {}

    bool has_next() const override {
        if (!sequence_) {
            return false;
        }
        return (current_ < sequence_->get_length());
    }

    T read() override {
        if (!has_next()) {
            throw EndOfStreamException();
        }
        T value = sequence_->get(current_);
        ++current_;
        return value;
    }

};