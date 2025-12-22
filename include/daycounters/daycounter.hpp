#pragma once

#include "types.hpp"

class Daycounter {
public:
    virtual float count(const Date& start, const Date& end) const = 0;
};
