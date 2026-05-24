#pragma once
#include <memory>
#include <functional>
#include <string>

template<typename T>
using Deserializer = std::function<T(const std::string&)>;

template<typename T>
class InputStream {
public:
    virtual ~InputStream() = default;
    virtual bool has_next() const = 0;
    virtual T read() = 0;
};