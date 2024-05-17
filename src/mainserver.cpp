#include <iostream>

#include "card.hpp"
#include "deck.hpp"
#include "player.hpp"

int main() {
    using namespace poker;

    Card c;
    std::cout << c << std::endl;
    c.suit = Card::Suit::Hearts;
    c.number = Card::Number::Ace;
    std::cout << c << std::endl;

    Deck d;
    std::cout << d << std::endl;
    Player p;
    p.set_hand({d.pick_card(), d.pick_card()});
    std::cout << p << std::endl;

    return 0;
}
