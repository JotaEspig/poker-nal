#pragma once

#include <array>
#include <ostream>

#include "card.hpp"

namespace poker {

class Deck {
public:
    Deck();

    void restart();
    void shuffle();
    std::array<Card, 52> cards() const;

    friend std::ostream &operator<<(std::ostream &os, const Deck &deck);

private:
    std::array<Card, 52> _cards;

    void generate_deck();
};

} // namespace poker
