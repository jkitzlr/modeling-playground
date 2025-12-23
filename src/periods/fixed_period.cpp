#include "boost/date_time/gregorian/gregorian.hpp"

#include "daycounters/daycounter.hpp"
#include "marketdata/marketdata.hpp"
#include "periods/fixed_period.hpp"
#include "scheduling/schedule_period.hpp"
#include "types.hpp"

FixedPeriod::FixedPeriod(const SchedulePeriod& pd,
                         float rate,
                         std::uint8_t pay_delay,
                         bool adjusted)
    : _rate(rate) {
    if (adjusted) {
        _start = pd.start();
        _end = pd.end();
    } else {
        _start = pd.unadj_start();
        _end = pd.unadj_end();
    }

    // ! this is wrong!
    _pay = pd.end() + boost::gregorian::days(pay_delay);
}

// TODO: consider returning optional instead; or raising?
float FixedPeriod::accrued(const Date& dt, const Daycounter& dc) const {
    if (is_past(dt) || is_after(dt)) {
        return std::nanf("");
    }

    return _rate * dc.count(_start, dt);
}

float FixedPeriod::cashflow(const Daycounter& dc, const MarketData* md) const {
    return accrued(_end, dc);
}
