#include <ostream>

#include "daycounters/daycounter.hpp"
#include "scheduling/schedule_period.hpp"

int SchedulePeriod::length_in_days() const { return (_end - _start).days(); }

float SchedulePeriod::year_fraction(const Daycounter& dc, bool adjusted) const {
    if (adjusted) {
        return dc.count(_start, _end);
    } else {
        return dc.count(_unadj_start, _unadj_end);
    }
}

bool SchedulePeriod::is_regular(const RollConvention& roll_conv,
                                const Tenor& tenor) const {
    return !is_stub(roll_conv, tenor);
}

bool SchedulePeriod::is_stub(const RollConvention& roll_conv,
                             const Tenor& tenor) const {
    return is_long(roll_conv, tenor) || is_short(roll_conv, tenor);
}

bool SchedulePeriod::is_long(const RollConvention& roll_conv,
                             const Tenor& tenor) const {
    return _unadj_end > roll_conv.next(_unadj_start, tenor);
}

bool SchedulePeriod::is_short(const RollConvention& roll_conv,
                              const Tenor& tenor) const {
    return _unadj_end < roll_conv.next(_unadj_start, tenor);
}

std::ostream& operator<<(std::ostream& os, const SchedulePeriod& p) {
    os << "start=" << p._start << " | end=" << p._end
       << " | unadj_start=" << p._unadj_start
       << " | unadj_end=" << p._unadj_end;
    return os;
}
