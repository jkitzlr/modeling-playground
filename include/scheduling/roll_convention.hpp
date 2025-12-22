#pragma once

#include "tenor.hpp"
#include "types.hpp"
#include "utils.hpp"

class RollConvention {
public:
    /// @brief Rolls the input date according to the convention
    /// @param date The date to roll
    /// @return The rolled date
    virtual Date roll(const Date& date) const = 0;

    /// @brief Calculate the next date in a date sequence (e.g. accrual sch)
    /// @param dt The date to adjust
    /// @param tenor The tenor to add to date
    /// @return The next date
    Date next(const Date& dt, const Tenor& tenor) const;

    /// @brief Calculate the prev date in a date sequence (e.g. accrual sch)
    /// @param dt The date to adjust
    /// @param tenor The tenor to add to date
    /// @return The next date
    Date previous(const Date& dt, const Tenor& tenor) const;
};

inline Date RollConvention::next(const Date& dt, const Tenor& tenor) const {
    return roll(dt + tenor);
}

inline Date RollConvention::previous(const Date& dt, const Tenor& tenor) const {
    return roll(dt - tenor);
}

/// @brief Roll dates to a specified day of the month.
class DayOfMonth : public RollConvention {
    std::uint8_t day;

public:
    DayOfMonth(std::uint32_t roll_day) : day(roll_day) {}

    Date roll(const Date& date) const override;
};

inline Date DayOfMonth::roll(const Date& date) const {
    auto const max_days = static_cast<std::uint8_t>(date.end_of_month().day());
    auto roll_day = min(day, max_days);
    return Date(date.year(), date.month(), roll_day);
}

class Bom : public RollConvention {
public:
    Date roll(const Date& date) const override {
        return Date(date.year(), date.month(), 1);
    }
};

class Eom : public RollConvention {
public:
    Date roll(const Date& date) const override { return date.end_of_month(); }
};
