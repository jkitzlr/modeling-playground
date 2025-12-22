#pragma once

#include "daycounters/daycounter.hpp"
#include "types.hpp"

class Act360 : public Daycounter {
public:
    float count(const Date& start, const Date& end) const override {
        auto days = static_cast<float>((end - start).days());
        return days / 360.0f;
    }
};
