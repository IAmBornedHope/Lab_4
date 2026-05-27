#pragma once
#include <memory>
#include <functional>
#include <string>

template<typename T>
using Deserializer = std::function<T(const std::string&)>;

class Deserializers {
public:
    static Deserializer<int> int_deserializer() {
        return [](const std::string& string) {
            return std::stoi(string);
        };
    }

    static Deserializer<double> double_deserializer() {
        return [](const std::string& string) {
            return std::stod(string);
        };
    }

    static Deserializer<std::string> string_deserializer() {
        return [](const std::string& string) {
            return string;
        };
    }
};



template<typename T>
class InputStream {
public:
    virtual ~InputStream() = default;
    virtual bool has_next() const = 0;
    virtual T read() = 0;
};