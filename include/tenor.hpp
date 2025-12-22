#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>

#include "types.hpp"

class Tenor {
public:
    virtual ~Tenor() = default;

    Date operator+(const Date& dt) const {
        // implement logic to add two tenors
        return add(dt);
    }

    friend Date operator+(const Date& lhs, const Tenor& rhs);

    friend Date operator-(const Date& lhs, const Tenor& rhs);

protected:
    // implement logic add the tenor to a date
    virtual Date add(const Date& dt) const = 0;

    // implement logic subtract the tenor to a date
    virtual Date sub(const Date& dt) const = 0;
};

inline Date operator+(const Date& lhs, const Tenor& rhs) {
    return rhs.add(lhs);
}

inline Date operator-(const Date& lhs, const Tenor& rhs) {
    return rhs.sub(lhs);
}

class Months : public Tenor {
    boost::gregorian::months months_;

public:
    Months(int n) : months_(n) {}

    ~Months() override = default;

protected:
    Date add(const Date& dt) const override { return dt + months_; }

    Date sub(const Date& dt) const override { return dt - months_; }
};
