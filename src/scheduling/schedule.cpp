#include <memory>
#include <optional>
#include <ostream>
#include <utility>
#include <vector>

#include "scheduling/adjuster.hpp"
#include "scheduling/roll_convention.hpp"
#include "scheduling/schedule.hpp"
#include "scheduling/schedule_period.hpp"
#include "tenor.hpp"

// TODO: raise exception if both eom and bom true
Schedule::Schedule(const Date& effective,
                   const Date& termination,
                   std::uint32_t months,
                   const BusinessCalendar& buscal,
                   const BusdayConvention& busday_conv,
                   bool eom,
                   bool bom,
                   const std::optional<Date>& front_stub,
                   const std::optional<Date>& back_stub)
    : adjuster(buscal, busday_conv) {
    tenor = new Months(months);

    Date start;

    if (front_stub) {
        // * emplace the first period which runs from effective to front_stub
        start = front_stub.value();
        periods.emplace_back(adjuster.adjust(effective), adjuster.adjust(start),
                             effective, start);
    } else {
        start = effective;
    }

    // * determine the roll convention
    init_roll_conv(static_cast<std::uint8_t>(start.day()), eom, bom);

    auto end = (back_stub) ? back_stub.value() : termination;

    // * handle the intermediate periods
    auto dt = start;
    while (dt < end) {
        auto next = roll_conv->next(dt, *tenor);
        periods.emplace_back(adjuster.adjust(dt), adjuster.adjust(next), dt,
                             next);
        dt = next;
    }

    // * handle back stub, if needed
    if (back_stub) {
        periods.emplace_back(adjuster.adjust(back_stub.value()),
                             adjuster.adjust(termination), back_stub.value(),
                             termination);
    }
}

std::ostream& operator<<(std::ostream& os, const Schedule& sch) {
    size_t i = 1;
    for (const auto& p : sch.periods) {
        os << "SchedulePeriod " << i << ": " << p << std::endl;
        i++;
    }
    return os;
}

// Schedule::Schedule(Schedule&& sch) noexcept
//     : adjuster(std::move(sch.adjuster)) {
//     roll_conv = sch.roll_conv;
//     periods = std::move(sch.periods);
//     tenor = sch.tenor;

//     // null out the old
//     sch.roll_conv = nullptr;
//     sch.tenor = nullptr;
// }
