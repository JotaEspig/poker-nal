#include <algorithm>
#include <ostream>
#include <random>
#include <vector>

#include "card.hpp"
#include "deck.hpp"

namespace poker {

Deck::Deck() {
    generate_deck();
}

void Deck::restart() {
    _cards.clear();
    generate_deck();
}

void Deck::shuffle() {
    std::random_device rd;
    std::default_random_engine engine{rd()};
    std::shuffle(_cards.begin(), _cards.end(), engine);
}

Card Deck::pick_card() {
    if (_cards.empty())
        return Card{};

    Card card = _cards.back();
    _cards.pop_back();
    return card;
}

const std::vector<Card> &Deck::cards() const {
    return _cards;
}

std::ostream &operator<<(std::ostream &os, const Deck &deck) {
    os << "[ ";
    auto it = deck._cards.begin();
    for (; it != deck._cards.end() - 1; ++it) {
        os << *it << ", ";
    }
    os << *it << " ]";
    return os;
}

void Deck::generate_deck() {
    for (int num = 1; num <= 13; ++num) {
        for (int suit = 1; suit <= 4; ++suit) {
            _cards.push_back(Card{
                static_cast<Card::Number>(num), static_cast<Card::Suit>(suit)
            });
        }
    }

    shuffle();
}

} // namespace poker
