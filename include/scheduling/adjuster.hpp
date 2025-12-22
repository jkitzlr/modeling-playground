#pragma once

#include <memory>

#include "buscal.hpp"

class Adjuster {
    std::shared_ptr<const BusinessCalendar> cal;
    BusdayConvention conv;

public:
    Adjuster(std::shared_ptr<const BusinessCalendar> cal,
             const BusdayConvention& conv)
        : cal(cal), conv(conv) {}

    Date adjust(const Date& dt) const;
};
