#pragma once

#include <vector>

#include "currency.hpp"
#include "daycounters/daycounter.hpp"
#include "marketdata/marketdata.hpp"
#include "scheduling/schedule.hpp"

/// @brief Represents a leg of an financial product.
template <typename Period>
class Leg {
public:
    // TODO
    class LegBuilder;

    /// @brief Get the schedule associated with this leg
    /// @return Schedule for the leg
    virtual const Schedule& schedule() const = 0;

    /// @brief Get the currency of payments for this leg
    /// @return Currency of the leg's payments
    virtual const Currency& currency() const = 0;

    virtual const BusinessCalendar& pay_cal() const = 0;

    virtual const Daycounter& daycounter() const = 0;

    // TODO: if I switch to Pimpl pattern, can use the Period interface directly
    virtual const std::vector<float>
    cashflows(const MarketData* marketdata) const = 0;
    // virtual const std::vector<float>& cashflows() const {
    //     std::vector<float> cfs;
    //     for (const auto& period : *this) {
    //         cfs.push_back(period.cashflow());
    //     }
    // }

    virtual ~Leg() = default;

    // * implement iterator protocol so make usable with range-based iterators
    auto begin() const { return _periods.begin(); }
    auto end() const { return _periods.end(); }

protected:
    std::vector<Period> _periods;
};
