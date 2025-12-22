#pragma once

#include <iostream>
#include <set>

#include "boost/date_time/gregorian/gregorian.hpp"

#include "types.hpp"

// TODO: move this to its own file
enum BusdayConvention {
    Following,
    Preceding,
    ModifiedFollowing,
    ModifiedPreceding,
    None
};

class BusinessCalendar {

    /// @brief Set of holidays
    std::set<Date> holidays;

    /// @brief Bitmask representing weekdays (1=weekday, 0=weekend)
    std::uint8_t mask;

    inline static std::uint8_t mask_arr[7] = {64, 32, 16, 8, 4, 2, 1};

public:
    /// @brief Default constructor initializing weekends to Saturday and Sunday.
    BusinessCalendar() : mask(0b1111100) {}

    template <typename Iterator>
    BusinessCalendar(const Iterator& start,
                     const Iterator& end,
                     const std::uint8_t weekend_mask = 0b1111100)
        : holidays(start, end), mask(weekend_mask) {}

    /// @brief Check if a given date is a holiday.
    /// @param dt The input date to check.
    /// @return True if the date is a holiday, false otherwise.
    bool is_holiday(const Date& dt) const {
        return (holidays.find(dt) != holidays.end());
    }

    /// @brief Check if a given date is a weekday.
    /// @param dt The input date to check.
    /// @return True if the date is a weekday, false otherwise.
    bool is_weekday(const Date& dt) const;

    /// @brief Check if a given date is a business day.
    /// @param dt The input date to check.
    /// @return True if the date is a business day, false otherwise.
    bool is_busday(const Date& dt) const {
        return is_weekday(dt) && !is_holiday(dt);
    }

    /// @brief Add calendar days to a given date.
    /// @param dt The starting date.
    /// @param days Number of calendar days to add.
    /// @return date The resulting date after adding the calendar days.
    Date add_caldays(const Date& dt, int days) const {
        return dt + boost::gregorian::days(days);
    }

    /// @brief Add business days to a given date.
    /// @param dt
    /// @param days
    /// @param roll_conv
    /// @return
    Date add_busdays(const Date& dt,
                     int days,
                     const BusdayConvention& roll_conv) const;

    /// @brief  Add months to a date.
    /// @param dt The starting date.
    /// @param months Number of months to add.
    /// @return date The resulting date after adding the months.
    Date add_months(const Date& dt, int months) const {
        return dt + boost::gregorian::months(months);
    }

    /// @brief Adjust the input ``dt`` according to ``roll_conv``.
    /// @param dt The input date to adjust.
    /// @param roll_conv The roll convention to apply.
    /// @return The adjusted date.
    Date adjust(const Date& dt, const BusdayConvention& roll_conv) const;

    /// @brief Print the holidays in the calendar.
    void print_holidays() const {
        if (holidays.empty()) {
            std::cout << "No holidays." << std::endl;
            return;
        }

        std::cout << "Holidays:" << std::endl;
        for (const auto& dt : holidays) {
            std::cout << dt << std::endl;
        }
    }

private:
    Date pred(const Date& dt) const;
    Date succ(const Date& dt) const;
};
