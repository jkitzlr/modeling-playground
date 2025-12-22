#pragma once

#include <ostream>
#include <string>

class Currency {
    std::string name;

public:
    Currency(const std::string& name);

    bool operator==(const Currency& other) const {
        return this->name == other.name;
    }

    friend std::ostream& operator<<(std::ostream& os, const Currency& currency);

    std::string value() const { return name; }
};
