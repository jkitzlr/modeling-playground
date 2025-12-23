#include <iostream>

#include "./test_utils.hpp"
#include "currencies.hpp"
#include "daycounters/act360.hpp"
#include "daycounters/daycounter.hpp"
#include "legs/fixed_leg.hpp"
#include "types.hpp"

int main() {
    auto pay_cal = test_cal();
    Daycounter* dc = new Act360();
    FixedLeg leg(Date(2024, 8, 15), Date(2026, 8, 15), 6, pay_cal,
                 BusdayConvention::Following, dc, 10e-2, Currencies::USD);

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
