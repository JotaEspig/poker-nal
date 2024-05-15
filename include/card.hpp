#pragma once

#include <ostream>

namespace poker {

struct Card {
    enum class Suit { Invalid = 0, Diamonds, Spades, Hearts, Clubs };
    enum class Number {
        Invalid = 0,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King,
        Ace
    };

    Number number;
    Suit suit;

    Card();
    Card(Number number, Suit suit);

    friend std::ostream &operator<<(std::ostream &os, const Card &card);
};

std::ostream &operator<<(std::ostream &os, const Card::Suit &suit);
std::ostream &operator<<(std::ostream &os, const Card::Number &number);

} // namespace poker
