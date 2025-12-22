#include <cassert>
#include <iostream>

#include "currencies.hpp"
#include "currency.hpp"

int main() {
    Currency usd("usd");
    assert(usd.value() == "USD");

    std::cout << "USD: " << usd << std::endl;

    Currency usd2("usd");
    assert(usd == usd2);

    std::cout << "USD2: " << usd2 << std::endl;

    Currency eur("EUR");
    assert(!(usd == eur));

    std::cout << "EUR: " << eur << std::endl;

    // * test Currencies for shits and giggles
    auto aud = Currencies::AUD;
    assert(aud.value() == "AUD");
}
