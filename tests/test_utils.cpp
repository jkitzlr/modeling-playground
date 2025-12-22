#include "./test_utils.hpp"
#include "buscal.hpp"
#include "types.hpp"

#include <memory>
#include <string>
#include <vector>

std::shared_ptr<BusinessCalendar> test_cal() {
    std::string iso_strings[13] = {
        "20250101", "20250120", "20250217", "20250418", "20250526",
        "20250619", "20250704", "20250901", "20251013", "20251111",
        "20251127", "20251225", "20251231"};

    std::vector<Date> holidays;
    for (const auto& h : iso_strings) {
        holidays.push_back(boost::gregorian::date_from_iso_string(h));
    }

    auto cal =
        new BusinessCalendar(holidays.begin(), holidays.end(), 0b1111100);

    return std::shared_ptr<BusinessCalendar>(cal);
}
