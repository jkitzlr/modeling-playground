#pragma once

#include <ostream>

#include "daycounters/daycounter.hpp"
#include "scheduling/roll_convention.hpp"
#include "tenor.hpp"
#include "types.hpp"

class SchedulePeriod {
    Date _start;
    Date _end;
    Date _unadj_start;
    Date _unadj_end;

public:
    SchedulePeriod(const Date& start,
                   const Date& end,
                   const Date& unadj_start,
                   const Date& unadj_end)
        : _start(start), _end(end), _unadj_start(unadj_start),
          _unadj_end(unadj_end) {}

    const Date& start() const { return _start; }
    const Date& end() const { return _end; }
    const Date& unadj_start() const { return _unadj_start; }
    const Date& unadj_end() const { return _unadj_end; }

    /// @brief Get the length of the period in days.
    /// @return Length in days.
    int length_in_days() const;

    /// @brief Calc the year fraction of the period using ``daycounter``.
    /// @param dc The daycounter.
    /// @param adjusted Whether to calc the fraction using adjusted dates.
    /// @return The year fraction covered by the period.
    float year_fraction(const Daycounter& dc, bool adjusted = true) const;

    /// @brief Check if the period is regular based on the roll conv and tenor.
    /// @param roll_conv The roll convention used to generate notional dates.
    /// @param tenor The time period against which to check.
    /// @return Whether the period is regular.
    bool is_regular(const RollConvention& roll_conv, const Tenor& tenor) const;

    /// @brief Check if the period is a stub based on the roll conv and tenor.
    /// @param roll_conv The roll convention used to generate notional dates.
    /// @param tenor The time period against which to check.
    /// @return Whether the period is a stub.
    bool is_stub(const RollConvention& roll_conv, const Tenor& tenor) const;

    /// @brief Check if the period is a long stub based on the roll conv and
    /// tenor.
    /// @param roll_conv The roll convention used to generate notional dates.
    /// @param tenor The time period against which to check.
    /// @return Whether the period is a long stub.
    bool is_long(const RollConvention& roll_conv, const Tenor& tenor) const;

    /// @brief Check if the period is a short stub based on the roll conv and
    /// tenor.
    /// @param roll_conv The roll convention used to generate notional dates.
    /// @param tenor The time period against which to check.
    /// @return Whether the period is a short stub.
    bool is_short(const RollConvention& roll_conv, const Tenor& tenor) const;

    // * operator overloads
    friend std::ostream& operator<<(std::ostream& os,
                                    const SchedulePeriod& period);
};
