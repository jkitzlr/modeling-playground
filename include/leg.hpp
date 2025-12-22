#pragma once

#include "currency.hpp"
#include "scheduling/schedule.hpp"

// TODO: fill out the interface for this; TBD how to get cashflow, cashflows
/// @brief Represents a leg of an financial product.
template <typename Period>
class Leg {
public:
    /// @brief Get the schedule associated with this leg
    /// @return Schedule for the leg
    virtual const Schedule& schedule() const = 0;

    /// @brief Get the currency of payments for this leg
    /// @return Currency of the leg's payments
    virtual const Currency& currency() const = 0;

    virtual ~Leg() = default;
};
