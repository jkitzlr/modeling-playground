#include <iostream>
#include <set>
#include <vector>

#include "buscal.hpp"
#include "scheduling/adjuster.hpp"
#include "types.hpp"

int main() {
    std::vector<Date> holidays = {
        Date(2025, 1, 1),
        Date(2025, 12, 25),
    };
    BusinessCalendar cal(holidays.begin(), holidays.end());
    Adjuster adjuster(cal, BusdayConvention::Following);

    Date dt1(2025, 1, 1); // Holiday
    Date adj1 = adjuster.adjust(dt1);
    assert(adj1 == Date(2025, 1, 2));
    std::cout << "Original date: " << dt1 << ", Adjusted date: " << adj1
              << std::endl;
}
