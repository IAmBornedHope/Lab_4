#pragma once
#include "../libs/Lab_3/exceptions/Exceptions.hpp"
#include "OutputStream.hpp"

template<typename T>
class FileOutputStream: public OutputStream<T> {
private:
    FILE* file_ = nullptr;
    Serializer<T> serializer_;
    std::string separator_;

public:
    FileOutputStream(const std::string& filename, Serializer<T> serializer, const std::string& separator = " ")
        : serializer_{serializer}, separator_{separator} {
            file_ = fopen(filename.c_str(), "w");
            if (!file_) {
                throw EmptyListException();
            }
        }
    
    
    ~FileOutputStream() override {
        if (file_) {
            fclose(file_);
            file_ = nullptr;
        }
    }

    void write(const T& value) override {
        if (!file_) {
            throw EmptyListException();
        }

        std::string string_value = serializer_(value);
        fprintf(file_, "%s", string_value.c_str());
        fprintf(file_, "%s", separator_.c_str());

    }
};