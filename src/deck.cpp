#include <algorithm>
#include <cstddef>
#include <ctime>
#include <ostream>
#include <random>

#include "card.hpp"
#include "deck.hpp"

namespace poker {

Deck::Deck() {
    generate_deck();
}

void Deck::restart() {
    generate_deck();
}

void Deck::shuffle() {
    unsigned seed = std::time(NULL);
    std::default_random_engine engine{seed};
    std::shuffle(_cards.begin(), _cards.end(), engine);
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

    shuffle();
}

} // namespace poker
