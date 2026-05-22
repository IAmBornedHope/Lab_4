#pragma once
#include "libs/Lab_3/exceptions/Option.hpp"

class Cardinal {
private:
    Option<size_t> size_;

public:
    Cardinal() : size_{0} {}
    Cardinal(size_t size) : size_{size} {}

    static Cardinal omega() {
        Cardinal cardinal;
        cardinal.size_ = Option<size_t>();
        return cardinal;
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
};