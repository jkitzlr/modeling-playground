#include <iostream>
#include <optional>

#include "./test_utils.hpp"
#include "buscal.hpp"
#include "scheduling/schedule.hpp"

int main() {
    Date effective(2025, 8, 31);
    Date termination(2030, 8, 31);
    std::uint32_t months = 6;
    auto buscal = test_cal();
    Schedule sch(effective, termination, months, buscal,
                 BusdayConvention::ModifiedFollowing);
    std::cout << sch << std::endl;
}
