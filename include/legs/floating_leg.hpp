#pragma once

#include <memory>

#include "leg.hpp"
#include "rateindex.hpp"

class FloatingLeg {
public:
    class FloatingPeriod;
};

class FloatingLeg::FloatingPeriod : public Leg::Period {
private:
    Date _start;
    Date _end;
    Date _pay;
    std::shared_ptr<const RateIndex> _index;
};
