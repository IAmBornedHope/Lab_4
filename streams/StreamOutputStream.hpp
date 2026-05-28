#pragma once
#include "../libs/Lab_3/exceptions/Exceptions.hpp"
#include "OutputStream.hpp"
#include <memory>

template<typename T>
class StreamOutputStream: public OutputStream<T> {
private:
    std::shared_ptr<OutputStream<T>> stream_;
public:
    StreamOutputStream(std::shared_ptr<OutputStream<T>> stream) : stream_{stream} {}

    void write(const T& value) override {
        if (!stream_) {
            throw EndOfStreamException);
        }
        stream_->write(value);
    }
};