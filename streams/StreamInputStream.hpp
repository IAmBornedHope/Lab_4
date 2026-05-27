#pragma once
#include "InputStream.hpp"

template<typename T>
class StreamInputStream: public InputStream<T> {
private:
    std::shared_ptr<InputStream<T>> stream_;

public:
    StreamInputStream(std::shared_ptr<InputStream<T>> stream) : stream_{stream} {}

    bool has_next() const override {
        if (!stream_) {
            return false;
        }
        return stream_->has_next();
    }

    T read() override {
        if (!has_next()) {
            throw EmptyListException();
        }
        return stream_->read();
    }
};