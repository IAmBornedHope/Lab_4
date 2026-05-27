#pragma once
#include <functional>
#include <string>

template<typename T>
using Serializer = std::function<std::string(const T&)>;

class Serializers {
public:
    static Serializer<int> int_serializer() {
        return [](int value) {
            return std::to_string(value);
        };
    }
    
    static Serializer<double> double_serializer() {
        return [](double value) {
            return std::to_string(value);
        };
    }

    static Serializer<std::string> string_serializer() {
        return [](const std::string& value) {
            return value;
        };
    }
};

template<typename T>
class OutputStream {
public:
    virtual ~OutputStream() = default;
    virtual void write(const T& value) = 0;
};