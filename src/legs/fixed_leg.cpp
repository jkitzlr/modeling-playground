#include <memory>
#include <utility>
#include <vector>

#include "buscal.hpp"
#include "legs/fixed_leg.hpp"
#include "marketdata/marketdata.hpp"
#include "types.hpp"

FixedLeg::FixedLeg(Schedule sch,
                   const Currency& ccy,
                   const BusinessCalendar& pay_cal,
                   const Daycounter* dc,
                   float rate,
                   bool adjust) noexcept
    : _sch(std::move(sch)), _ccy(ccy),
      _cal(std::make_shared<BusinessCalendar>(pay_cal)), _dc(dc) {
    for (const auto& period : _sch) {
        _periods.emplace_back(period, rate, 0, adjust);
    }
}

FixedLeg::FixedLeg(const Date& effective,
                   const Date& termination,
                   std::uint32_t months,
                   const BusinessCalendar& pay_cal,
                   const BusdayConvention& busday_conv,
                   const Daycounter* dc,
                   float rate,
                   const Currency& ccy,
                   bool eom,
                   bool bom,
                   const std::optional<Date>& front_stub,
                   const std::optional<Date>& back_stub,
                   bool adjust) noexcept
    : FixedLeg(Schedule(effective,
                        termination,
                        months,
                        pay_cal,
                        busday_conv,
                        eom,
                        bom,
                        front_stub,
                        back_stub),
               ccy,
               pay_cal,
               dc,
               rate,
               adjust) {}

const std::vector<float>
FixedLeg::cashflows(const MarketData* marketdata) const {
    std::vector<float> cfs;
    for (const auto& period : _periods) {
        cfs.push_back(period.cashflow(*_dc, marketdata));
    }
    return cfs;
}

std::vector<Date> FixedLeg::pay_dates() const {
    std::vector<Date> dts;
    for (const auto& period : _periods) {
        dts.push_back(period._pay);
    }
    return dts;
}
