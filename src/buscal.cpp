#include "buscal.hpp"
#include "types.hpp"

bool BusinessCalendar::is_weekday(const Date& dt) const {
    // mon = 0, tue = 1, etc.
    auto wd = static_cast<int>(dt.day_of_week()) - 1;
    return (mask & mask_arr[wd]) != 0;
}

Date BusinessCalendar::adjust(const Date& dt,
                              const BusdayConvention& roll_conv) const {
    if (is_busday(dt))
        return dt;

    switch (roll_conv) {
        case BusdayConvention::None:
            return dt;
        case BusdayConvention::Following:
            return succ(dt);
        case BusdayConvention::Preceding:
            return pred(dt);
        case BusdayConvention::ModifiedFollowing: {
            auto adj = succ(dt);
            if (adj.month() != dt.month()) {
                return pred(dt);
            }
        }
        case BusdayConvention::ModifiedPreceding: {
            auto adj = pred(dt);
            if (adj.month() != dt.month()) {
                return succ(dt);
            }
        }
        // ! need to think this one through
        default:
            return dt;
    }
}

Date BusinessCalendar::pred(const Date& dt) const {
    auto curr = dt - boost::gregorian::days(1);
    while (!is_busday(curr)) {
        curr = curr - boost::gregorian::days(1);
    }
    return curr;
}

Date BusinessCalendar::succ(const Date& dt) const {
    auto curr = dt + boost::gregorian::days(1);
    while (!is_busday(curr)) {
        curr = curr + boost::gregorian::days(1);
    }
    return curr;
}
