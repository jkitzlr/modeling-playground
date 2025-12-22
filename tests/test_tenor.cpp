#include <iostream>
#include <memory>

#include "tenor.hpp"

int main() {
    auto tenor = std::make_shared<Months>(6);
    Date dt(2023, 8, 31);
    auto dt2 = dt + (*tenor);

    assert(dt2 == Date(2024, 2, 29));
    std::cout << "Original date: " << dt << ", New date: " << dt2 << std::endl;

    auto dt3 = dt - (*tenor);
    assert(dt3 == Date(2023, 2, 28));
    std::cout << "Original date: " << dt << ", New date: " << dt3 << std::endl;
}
