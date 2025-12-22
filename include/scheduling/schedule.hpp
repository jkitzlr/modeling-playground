#pragma once

#include <memory>
#include <optional>
#include <ostream>
#include <vector>

#include "buscal.hpp"
#include "scheduling/adjuster.hpp"
#include "scheduling/roll_convention.hpp"
#include "scheduling/schedule_period.hpp"
#include "tenor.hpp"
#include "types.hpp"

class Schedule {
    std::vector<SchedulePeriod> periods;
    RollConvention* roll_conv;
    Adjuster adjuster;
    Tenor* tenor;

public:
    // TODO(jkitzlr): replace months with tenor string (will figure that out
    // later)
    Schedule(const Date& effective,
             const Date& termination,
             std::uint32_t months,
             std::shared_ptr<const BusinessCalendar> buscal,
             const BusdayConvention& busday_conv,
             bool eom = false,
             bool bom = false,
             const std::optional<Date>& front_stub = std::nullopt,
             const std::optional<Date>& back_stub = std::nullopt);

    // * operator overloads
    friend std::ostream& operator<<(std::ostream& os, const Schedule& sch);

protected:
    // * keep this protected so that clients aren't fucking with allocations
    // * and we can fully manage the lifetimes of the allocated objects
    Schedule(std::vector<SchedulePeriod> periods,
             RollConvention* roll_conv,
             Adjuster adjuster,
             Tenor* tenor)
        : periods(std::move(periods)), roll_conv(roll_conv), adjuster(adjuster),
          tenor(tenor) {}

private:
    void init_roll_conv(std::uint8_t day, bool eom, bool bom);
};

inline void Schedule::init_roll_conv(std::uint8_t day, bool eom, bool bom) {
    if (eom) {
        roll_conv = new Eom();
    } else if (bom) {
        roll_conv = new Bom();
    } else {
        roll_conv = new DayOfMonth(day);
    }
}
