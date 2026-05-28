#pragma once
#include "../libs/Lab_3/exceptions/Exceptions.hpp"
#include "InputStream.hpp"

template<typename T>
class FileInputStream: public InputStream<T> {
private:
    FILE* file_ = nullptr;
    Deserializer<T> deserializer_;
    std::string separator_;
    std::string buffer_;
    bool is_end = false;

    void fill_buffer() {
        while (buffer_.find(separator_) == std::string::npos && !is_end) {
            char temp[256];
            size_t count = fread(temp, 1, 256, file_);

            if (count > 0) {
                buffer_.append(temp, count);
            }
            else {
                is_end = true;
            }
        }
    }

public:
    FileInputStream(const std::string& filename, Deserializer<T> deserializer, const std::string& separator = " ")
        : deserializer_{deserializer}, separator_{separator} {
            file_ = fopen(filename.c_str(), "r");
            if (!file_) {
                throw FileOpenException(filename);
            }
            fill_buffer();
        }

    ~FileInputStream() override {
        if (file_) {
            fclose(file_);
            file_ = nullptr;
        }
    }

    bool has_next() const override {
        return !buffer_.empty();
    }

    T read() override {
        fill_buffer();

        std::string token;
        size_t separator_pos = buffer_.find(separator_);

        if (separator_pos != std::string::npos) {
            token = buffer_.substr(0, separator_pos);
            buffer_.erase(0, separator_pos + separator_.length());
        }
        else {
            token = buffer_;
            buffer_.clear();
        }

        if (token.empty()) {
            return read();
        }

        return deserializer_(token);
    }
};