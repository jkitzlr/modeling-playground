#include <optional>
#include <string>

#include "boost/date_time/gregorian/gregorian.hpp"

#include "buscal.hpp"
#include "currency.hpp"
#include "daycounters/daycounter.hpp"
#include "secmaster.hpp"
#include "types.hpp"

SecMaster::SecMaster(std::string eff,
                     std::string start,
                     std::string end,
                     std::string term,
                     std::uint32_t months,
                     std::string cal, // the NAME of the pay cal
                     std::string adj_conv,
                     std::string dcc,
                     std::string ccy,
                     float cpn,
                     bool eom,
                     bool adj_end_dt) noexcept
    : effective_(boost::gregorian::from_undelimited_string(eff)),
      front_stub_(std::nullopt), back_stub_(std::nullopt),
      termination_(boost::gregorian::from_undelimited_string(term)),
      months_(months), cal(cal), dcc_(dcc), ccy_(ccy), cpn(cpn), eom(eom),
      adj_end_dt(adj_end_dt) {
    busday_conv_ = get_busday_conv(adj_conv);

    if (!start.empty()) {
        front_stub_ = std::optional<Date>(
            boost::gregorian::from_undelimited_string(start));
    }

    if (!end.empty()) {
        back_stub_ =
            std::optional<Date>(boost::gregorian::from_undelimited_string(end));
    }
}

const Date& SecMaster::effective() const { return effective_; }

const Date& SecMaster::termination() const { return termination_; }

const std::uint32_t SecMaster::months() const { return months_; }

const std::string& SecMaster::pay_cal() const { return cal; }

const BusdayConvention SecMaster::busday_conv() const {
    return BusdayConvention::Following;
}

const std::string& SecMaster::dcc() const { return dcc_; }

float SecMaster::rate() const { return cpn; }

const Currency& SecMaster::currency() const { return ccy_; }
