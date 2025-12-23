#pragma once

#include <optional>

#include "daycounters/daycounter.hpp"
#include "marketdata/marketdata.hpp"
#include "scheduling/schedule_period.hpp"
#include "types.hpp"

// TODO: should this store ex-div date or let caller deal with that?
// TODO: should this store a notional--or have a separate class for indexed,
// accreting, amortizing, etc. coupons?

/// @brief A payment period over which a fixed rate accrues
class FixedPeriod {
    Date _start;
    Date _end;
    Date _pay;
    float _rate;

public:
    /// @brief Direct constructor of the FixedPeriod
    /// @param start Accrual start date of the period
    /// @param end Accrual end date of the period
    /// @param pay The date the payment for the period is made
    /// @param rate The fixed rate
    FixedPeriod(const Date& start, const Date& end, const Date& pay, float rate)
        : _start(start), _end(end), _pay(pay), _rate(rate) {}

    // TODO: need to take in a busday cal to compute pay delay
    /// @brief Construct the FixedPeriod from a SchedulePeriod
    /// @param pd SchedulePeriod
    /// @param rate The fixed rate for the period
    /// @param pay_delay Optional pay delay; if 0, uses adjusted end dt
    /// @param adjusted Whether to set accrual date as adjusted start/end
    FixedPeriod(const SchedulePeriod& pd,
                float rate,
                std::uint8_t pay_delay = 0,
                bool adjusted = false);

    /// @brief Calculate accrued interest for the period
    /// @param dt the date through which to calc accrued interest
    /// @param dc The daycounter to use to calc the year frac
    /// @return Accrued interest or NaN if invalid date
    float accrued(const Date& dt, const Daycounter& dc) const;

    /// @brief Calculate the cashflow payable for the period
    /// @param dc The daycounter to use to calc the amount
    /// @param marketdata Optional market data to provide any needed data to
    /// project cashflow
    /// @return The cashflow amount
    float cashflow(const Daycounter& dc,
                   const MarketData* marketdata = nullptr) const;

    /// @brief Check if ``dt`` is after the end of the period
    /// @param dt The date to check
    /// @return If period is in the past relative to ``dt``
    bool is_past(const Date& dt) const { return dt > _end; }

    /// @brief Check if ``dt`` is before the start of the period
    /// @param dt The date to check
    /// @return If period is after ``dt``
    bool is_after(const Date& dt) const { return dt < _start; }

    friend class FixedLeg;
};
