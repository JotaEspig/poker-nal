#include <ostream>

#include "card.hpp"

namespace poker {

Card::Card() :
  number{Number::Invalid},
  suit{Suit::Invalid} {
}

Card::Card(Number n, Suit s) :
  number{n},
  suit{s} {
}

std::ostream &operator<<(std::ostream &os, const Card &card) {
    os << card.number << "." << card.suit;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Card::Suit &suit) {
    using Suit = Card::Suit;
#ifdef NOEMOJI
    switch (suit) {
    case Suit::Diamonds:
        os << "Diamonds";
        break;
    case Suit::Spades:
        os << "Spades";
        break;
    case Suit::Hearts:
        os << "Hearts";
        break;
    case Suit::Clubs:
        os << "Clubs";
        break;
    case Suit::Invalid:
        os << "Invalid";
    }
#else
    switch (suit) {
        case Suit::Diamonds:
            os << "♦️";
            break;
    case Suit::Spades:
        os << "♠️";
        break;
    case Suit::Hearts:
        os << "♥️";
        break;
    case Suit::Clubs:
        os << "♣️";
        break;
    case Suit::Invalid:
        os << "Invalid";
    }
#endif
    return os;
}
std::ostream &operator<<(std::ostream &os, const Card::Number &number) {
    using Number = Card::Number;
    switch (number) {
    case Number::Two:
        os << "2";
        break;
    case Number::Three:
        os << "3";
        break;
    case Number::Four:
        os << "4";
        break;
    case Number::Five:
        os << "5";
        break;
    case Number::Six:
        os << "6";
        break;
    case Number::Seven:
        os << "7";
        break;
    case Number::Eight:
        os << "8";
        break;
    case Number::Nine:
        os << "9";
        break;
    case Number::Ten:
        os << "10";
        break;
    case Number::Jack:
        os << "J";
        break;
    case Number::Queen:
        os << "Q";
        break;
    case Number::King:
        os << "K";
        break;
    case Number::Ace:
        os << "A";
        break;
    case Number::Invalid:
        os << "Invalid";
    }
    return os;
}

} // namespace poker
