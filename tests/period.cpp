#include <iostream>

#include "scheduling/schedule_period.hpp"
#include "types.hpp"

int main() {
    SchedulePeriod pd(Date(2025, 8, 29), Date(2026, 2, 27), Date(2025, 8, 31),
                      Date(2026, 2, 28));
    std::cout << pd << std::endl;
}