#pragma once
#include "libs/Lab_3/exceptions/Option.hpp"

class Cardinal {
private:
    Option<size_t> size_;

    Cardinal() : size_{} {}

public:
    Cardinal(size_t size) : size_{size} {}

    static Cardinal aleph_null() {
        return Cardinal{};
    }
    
    bool is_finite() const {
        return size_.has_value();
    }

    bool is_infinite() const {
        return !size_.has_value();
    }

    Option<size_t> try_get_size() const {
        return size_;
    }

    size_t get_size() const {
        if (is_infinite()) {
            throw IndexOutOfRangeException("Нельзя получить бесконечность");
        }
        return size_.get_value();
    }

    bool operator==(const Cardinal& cardinal) const {
        if (is_infinite() && cardinal.is_infinite()) {
            return true;
        }
        if (is_infinite() || cardinal.is_infinite()) {
            return false;
        }
        return size_.get_value() == cardinal.size_.get_value();
    }

    bool operator!=(const Cardinal& cardinal) const {
        return !(*this == cardinal);
    }
    
    bool operator<(const Cardinal& cardinal) const {
        if (is_infinite()) {
            return false;
        }
        if (cardinal.is_infinite()) {
            return true;
        }
        return size_.get_value() < cardinal.size_.get_value();
    }

    bool operator>(const Cardinal& cardinal) const {
        return cardinal < *this;
    }

    bool operator<=(const Cardinal& cardinal) const {
        return (*this < cardinal) || (*this == cardinal);
    }

    bool operator>=(const Cardinal& cardinal) const {
        return (*this > cardinal) || (*this == cardinal);
    }

    Cardinal operator+(const Cardinal& cardinal) const {
        if (is_infinite() || cardinal.is_infinite()) {
            return Cardinal::aleph_null();
        }
        return Cardinal(size_.get_value() + cardinal.size_.get_value());
    }
};