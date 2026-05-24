#pragma once
#include <functional>
#include <string>

template<typename T>
using Serializer = std::function<std::string(const T&)>;

template<typename T>
class OutputStream {
public:
    virtual ~OutputStream() = default;
    virtual void write(const T& value) = 0;
};