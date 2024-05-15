#include <cstddef>
#include <ostream>

#include "card.hpp"
#include "deck.hpp"

namespace poker {

Deck::Deck() {
    generate_deck();
}

std::array<Card, 52> Deck::cards() const {
    return _cards;
}

std::ostream &operator<<(std::ostream &os, const Deck &deck) {
    os << "[ ";
    std::array<const Card, 52>::iterator it;
    for (it = deck._cards.begin(); it != deck._cards.end() - 1; ++it) {
        os << *it << ", ";
    }
    os << *it << " ]";
    return os;
}

void Deck::generate_deck() {
    std::size_t index = 0;
    for (int num = 1; num <= 13; ++num) {
        for (int suit = 1; suit <= 4; ++suit) {
            _cards[index++] = Card{
                static_cast<Card::Number>(num), static_cast<Card::Suit>(suit)
            };
        }
    }
}

} // namespace poker
