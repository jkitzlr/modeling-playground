#pragma once

#include <optional>
#include <string>

#include "buscal.hpp"
#include "currency.hpp"
#include "daycounters/daycounter.hpp"
#include "types.hpp"
#include "utils.hpp"

class SecMaster {
    Date effective_;
    std::optional<Date> front_stub_;
    std::optional<Date> back_stub_;
    Date termination_;
    std::uint32_t months_;
    std::string cal; // the NAME of the pay cal
    BusdayConvention busday_conv_;
    std::string dcc_;
    Currency ccy_;
    float cpn;
    bool eom;
    bool adj_end_dt;

public:
    SecMaster(std::string eff,
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
              bool adj_end_dt) noexcept;

    const Date& effective() const;

    const Date& termination() const;

    const std::uint32_t months() const;

    const std::string& pay_cal() const;

    const BusdayConvention busday_conv() const;

    const std::string& dcc() const;

    float rate() const;

    const Currency& currency() const;

private:
    BusdayConvention get_busday_conv(const std::string& input) const;
    const Daycounter* get_daycounter(const std::string& input) const;
};

inline BusdayConvention
SecMaster::get_busday_conv(const std::string& input) const {
    auto lower = tolower_new(input);
    if (lower == "following") {
        return BusdayConvention::Following;
    }

    // TODO: is the best way to handle this?
    return BusdayConvention::None;
}
