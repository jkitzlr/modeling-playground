#include <ostream>
#include <string>

#include "currency.hpp"

Currency::Currency(const std::string& name) {
    if (name.length() != 3) {
        throw std::invalid_argument("Currency code must be 3 characters long");
    }

    this->name = name;

    for (auto& c : this->name) {
        c = std::toupper(c);
    }
}

std::ostream& operator<<(std::ostream& os, const Currency& currency) {
    os << currency.value();
    return os;
}
