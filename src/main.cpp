#include <iostream>

#include "card.hpp"
#include "deck.hpp"

int main() {
    using namespace poker;

    Card c;
    std::cout << c << std::endl;
    c.suit = Card::Suit::Hearts;
    c.number = Card::Number::Ace;
    std::cout << c << std::endl;

    Deck d;
    std::cout << d << std::endl;

    return 0;
}
