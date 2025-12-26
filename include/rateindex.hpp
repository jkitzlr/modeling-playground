#pragma once

#include <string>

#include "buscal.hpp"
#include "currency.hpp"
#include "daycounters/daycounter.hpp"
#include "tenor.hpp"

/// @brief Store reference data about a specific interest rate index
class RateIndex {
public:
    /// @brief Get the name of the index
    virtual std::string& name() const = 0;

    /// @brief Get the currency of the index
    virtual Currency& currency() const = 0;

    /// @brief Get the daycounter implementing the index's daycount convention
    virtual const Daycounter& daycounter() const = 0;

    /// @brief Get the tenor of the index
    virtual const Tenor& tenor() const = 0;

    /// @brief Get the business calendar used to calc valid fixing dates
    virtual const BusinessCalendar& fixing_cal() const = 0;
};
