#include <iostream>

#include "scheduling/roll_convention.hpp"
#include "tenor.hpp"
#include "types.hpp"

int main() {
    // test cases
    Date dt1(2023, 2, 17);
    Date dt2(2024, 2, 17);
    Date dt3(2025, 8, 29);

    // * DayOfMonth
    DayOfMonth dom1(15);
    DayOfMonth dom2(31);

    assert(dom1.roll(dt1) == Date(2023, 2, 15));
    assert(dom1.roll(dt2) == Date(2024, 2, 15));
    assert(dom1.roll(dt3) == Date(2025, 8, 15));

    assert(dom2.roll(dt1) == Date(2023, 2, 28));
    assert(dom2.roll(dt2) == Date(2024, 2, 29));
    assert(dom2.roll(dt3) == Date(2025, 8, 31));

    // * check next/previous
    Date dt(2024, 8, 29);
    Months tenor(6);
    assert(dom2.next(dt, tenor) == Date(2025, 2, 28));
    assert(dom2.previous(dt, tenor) == Date(2024, 2, 29));
}
