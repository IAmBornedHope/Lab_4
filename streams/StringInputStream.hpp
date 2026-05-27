#pragma once
#include "InputStream.hpp"
#include "../libs/Lab_3/array_sequence/ArraySequence.hpp"

template<typename T>
class StringInputStream: public InputStream<T> {
private:
    std::string string_;
    Deserializer<T> deserializer_;
    std::string separator_;

public:
    StringInputStream(std::string string, Deserializer<T> deserializer, const std::string& separator = " ")
        : string_(std::move(string)), deserializer_{deserializer}, separator_{separator} {}

    bool has_next() const override {
        return !string_.empty();
    }

    T read() override {
        if (!has_next()) {
            throw EmptyListException();
        }
        std::string token;
        size_t separator_pos = string_.find(separator_);


        if (separator_pos != std::string::npos) {
            token = string_.substr(0, separator_pos);
            string_.erase(0, separator_pos + separator_.length());
        }
        else {
            token = string_;
            string_.clear();
        }

        if (token.empty()) {
            return read();
        }

        return deserializer_(token);
    }
};