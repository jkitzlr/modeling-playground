#include <iostream>
#include <string>

#include "boost/date_time/gregorian/gregorian.hpp"

#include "./test_utils.hpp"
#include "currencies.hpp"
#include "daycounters/act360.hpp"
#include "daycounters/daycounter.hpp"
#include "legs/fixed_leg.hpp"
#include "secmaster.hpp"
#include "types.hpp"
#include "utils.hpp"

SecMaster leg_data() {
    SecMaster sm("20240815", "", "", "20260815", 6, "FD", "following",
                 "ACT/360", "USD", 10e-2, false, false);
    return sm;
}

int main() {
    auto pay_cal = test_cal();
    Daycounter* dc = new Act360();
    auto sm = leg_data();
    // FixedLeg leg(Date(2024, 8, 15), Date(2026, 8, 15), 6, pay_cal,
    //              BusdayConvention::Following, dc, 10e-2, Currencies::USD);
    FixedLeg leg(sm.effective(), sm.termination(), sm.months(), pay_cal,
                 sm.busday_conv(), dc, sm.rate(), sm.currency());

    auto cfs = leg.cashflows(nullptr);
    auto dates = leg.pay_dates();

    std::cout << "Dates: " << std::endl;
    for (const auto& dt : dates) {
        std::cout << dt << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Cashflows: " << std::endl;
    for (const auto& cf : cfs) {
        std::cout << cf << std::endl;
    }
}
