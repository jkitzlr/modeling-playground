#include "scheduling/adjuster.hpp"

Date Adjuster::adjust(const Date& dt) const {
    if (conv == BusdayConvention::None) {
        return dt;
    }
    return cal->adjust(dt, conv);
}
