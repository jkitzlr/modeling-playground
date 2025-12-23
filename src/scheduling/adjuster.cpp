#include <utility>

#include "scheduling/adjuster.hpp"

Date Adjuster::adjust(const Date& dt) const {
    if (conv == BusdayConvention::None) {
        return dt;
    }
    return cal->adjust(dt, conv);
}

// Adjuster::Adjuster(Adjuster&& other) noexcept {
//     cal = std::move(other.cal);
//     conv = other.conv;
// }
