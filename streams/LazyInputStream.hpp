#pragma once
#include "InputStream.hpp"
#include "../libs/Lab_3/exceptions/Exceptions.hpp"
#include "../lazy_sequence/LazySequence.hpp"

template<typename T, template<typename> class Container>
class LazyInputStream: public InputStream<T> {
private:
    std::shared_ptr<LazySequence<T, Container>> sequence_;
    size_t current_ = 0;

public:
    LazyInputStream(std::shared_ptr<LazySequence<T, Container>> sequence) : sequence_{sequence} {}
    LazyInputStream(const Container<T>& container) : sequence_{std::make_shared<LazySequence<T, Container>>(container)} {}

    bool has_next() const override {
        if (!sequence_) {
            return false;
        }

        Cardinal length = sequence_->get_length();
        if (length.is_infinite()) {
            return true;
        }
        return current_ < length.get_size();
    }

    T read() override {
        if (!has_next()) {
            throw EmptyListException();
        }
        T value = sequence_->get(Cardinal(current_));
        ++current_;
        return value;
    }

};

template<typename T, template<typename> class Container>
std::ostream& operator<<(std::ostream& stream, LazyInputStream<T, Container>& input_stream) {
    bool first = true;
    while (input_stream.has_next()) {
        if (!first) {
            stream << " ";
        }
        stream << input_stream.read();
        first = false;
    }
    return stream;
}

