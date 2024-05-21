#include <array>

#include "card.hpp"
#include "utils.hpp"

namespace poker {

bool is_pair(std::array<Card, 7> all_cards) {
    for (size_t i = 0; i < 7; ++i) {
            Card c1 = all_cards[i];
        for (size_t j = 0; j < 7; ++j) {
            if (i == j)
                continue;

            Card c2 = all_cards[j];
            if (c1.number == c2.number)
                return true;
        }
    }

    return false;
}

} // namespace poker
