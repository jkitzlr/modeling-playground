#pragma once

#include <memory>

#include "buscal.hpp"
#include "currency.hpp"
#include "leg.hpp"
#include "marketdata/marketdata.hpp"
#include "periods/fixed_period.hpp"

class FixedLeg : public Leg<FixedPeriod> {
    Schedule _sch;
    const Currency _ccy;
    const std::shared_ptr<BusinessCalendar> _cal;
    const Daycounter* _dc;

public:
    /// @brief Construct the fixed leg from Schedule and other params
    /// @param sch Schedule--note that this is MOVED into FixedLeg
    /// @param ccy The currency of the leg's payments
    /// @param pay_cal Payment calendar to adjust accrual and payment dates
    /// @param dc Daycounter to compute accrued and coupons
    /// @param rate the fixed rate for each period
    /// @param adjust Whether the payment periods should start/end on adjusted
    /// dates
    FixedLeg(Schedule sch,
             const Currency& ccy,
             const BusinessCalendar& pay_cal,
             const Daycounter* dc,
             float rate,
             bool adjust = false) noexcept;

    FixedLeg(const Date& effective,
             const Date& termination,
             std::uint32_t months,
             const BusinessCalendar& pay_cal,
             const BusdayConvention& busday_conv,
             const Daycounter* dc,
             float rate,
             const Currency& ccy,
             bool eom = false,
             bool bom = false,
             const std::optional<Date>& front_stub = std::nullopt,
             const std::optional<Date>& back_stub = std::nullopt,
             bool adjust = false) noexcept;

    const Schedule& schedule() const override { return _sch; }

    const Currency& currency() const override { return _ccy; }

    const BusinessCalendar& pay_cal() const override { return *_cal; }

    const Daycounter& daycounter() const override { return *_dc; }

    const std::vector<float>
    cashflows(const MarketData* marketdata) const override;

    // TODO: this needs to be part of the base Leg interface
    std::vector<Date> pay_dates() const;
};
