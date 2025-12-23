#pragma once

#include <memory>

#include "buscal.hpp"

class Adjuster {
    std::shared_ptr<const BusinessCalendar> cal;
    BusdayConvention conv;

public:
    Adjuster(const BusinessCalendar& cal, const BusdayConvention& conv)
        : cal(std::make_shared<const BusinessCalendar>(cal)), conv(conv) {}

    // ! use auto-generate move constructor; avoid implicit deletion of copy
    // Adjuster(Adjuster&& other) noexcept;

    Date adjust(const Date& dt) const;
};
