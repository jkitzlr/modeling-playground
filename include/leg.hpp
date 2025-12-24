#pragma once

#include <vector>

#include "currency.hpp"
#include "daycounters/daycounter.hpp"
#include "marketdata/marketdata.hpp"
#include "scheduling/schedule.hpp"

/// @brief Represents a leg of an financial product.
class Leg {
public:
    // TODO
    class Period;
    class LegBuilder;

    /// @brief Get the schedule associated with this leg
    /// @return Schedule for the leg
    virtual const Schedule& schedule() const = 0;

    /// @brief Get the currency of payments for this leg
    /// @return Currency of the leg's payments
    virtual const Currency& currency() const = 0;

    virtual const BusinessCalendar& pay_cal() const = 0;

    virtual const Daycounter& daycounter() const = 0;

    // TODO: replace as "cashflows table" for reporting
    virtual const std::vector<float>
    cashflows(const MarketData* marketdata) const = 0;

    virtual std::vector<Date> pay_dates() const = 0;

    virtual ~Leg() = default;

protected:
};

class Leg::Period {
public:
    /// @brief Get the start date of the period
    virtual const Date& start() const = 0;

    /// @brief Get the end date of the period
    virtual const Date& end() const = 0;

    /// @ brief Get the pay date for the period
    virtual const Date& pay() const = 0;

    /// @brief Calculate accrued interest for the period
    /// @param dt the date through which to calc accrued interest
    /// @param dc The daycounter to use to calc the year frac
    /// @return Accrued interest or NaN if invalid date
    virtual float accrued(const Date& dt, const Daycounter& dc) const = 0;

    /// @brief Calculate the cashflow payable for the period
    /// @param dc The daycounter to use to calc the amount
    /// @param marketdata Optional market data to provide any needed data to
    /// project cashflow
    /// @return The cashflow amount
    virtual float cashflow(const Daycounter& dc,
                           const MarketData* marketdata = nullptr) const = 0;

    /// @brief Check if ``dt`` is after the end of the period
    /// @param dt The date to check
    /// @return If period is in the past relative to ``dt``
    bool is_past(const Date& dt) const { return dt > end(); }

    /// @brief Check if ``dt`` is before the start of the period
    /// @param dt The date to check
    /// @return If period is after ``dt``
    bool is_after(const Date& dt) const { return dt < start(); }
};
