#pragma once

#include <memory>

#include "buscal.hpp"
#include "currency.hpp"
#include "leg.hpp"
#include "marketdata/marketdata.hpp"

class FixedLeg : public Leg {

public:
    class FixedPeriod;

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
    std::vector<Date> pay_dates() const override;

private:
    Schedule _sch;
    const Currency _ccy;
    const std::shared_ptr<BusinessCalendar> _cal;
    const Daycounter* _dc;
    std::vector<FixedPeriod> _periods;
};

class FixedLeg::FixedPeriod : public Leg::Period {
    Date _start;
    Date _end;
    Date _pay;
    float _rate;

public:
    /// @brief Direct constructor of the FixedPeriod
    /// @param start Accrual start date of the period
    /// @param end Accrual end date of the period
    /// @param pay The date the payment for the period is made
    /// @param rate The fixed rate
    FixedPeriod(const Date& start, const Date& end, const Date& pay, float rate)
        : _start(start), _end(end), _pay(pay), _rate(rate) {}

    // TODO: need to take in a busday cal to compute pay delay
    /// @brief Construct the FixedPeriod from a SchedulePeriod
    /// @param pd SchedulePeriod
    /// @param rate The fixed rate for the period
    /// @param pay_delay Optional pay delay; if 0, uses adjusted end dt
    /// @param adjusted Whether to set accrual date as adjusted start/end
    FixedPeriod(const SchedulePeriod& pd,
                float rate,
                std::uint8_t pay_delay = 0,
                bool adjusted = false);

    const Date& start() const override { return _start; }

    /// @brief Get the end date of the period
    const Date& end() const override { return _end; }

    /// @ brief Get the pay date for the period
    const Date& pay() const override { return _pay; }

    /// @brief Calculate accrued interest for the period
    /// @param dt the date through which to calc accrued interest
    /// @param dc The daycounter to use to calc the year frac
    /// @return Accrued interest or NaN if invalid date
    float accrued(const Date& dt, const Daycounter& dc) const override;

    /// @brief Calculate the cashflow payable for the period
    /// @param dc The daycounter to use to calc the amount
    /// @param marketdata Optional market data to provide any needed data to
    /// project cashflow
    /// @return The cashflow amount
    float cashflow(const Daycounter& dc,
                   const MarketData* marketdata = nullptr) const override;
};
