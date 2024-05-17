#include <cstdint>
#include <utility>

#include "card.hpp"
#include "player.hpp"

namespace poker {

Player::Player() {
}

Player::Player(const std::pair<Card, Card> &cards) {
    set_hand(cards);
}

bool Player::can_bet(uint64_t value) {
    return _cash >= value;
}

uint64_t Player::bet(uint64_t value) {
    _cash -= value;
    return _cash;
}

uint64_t Player::receive(uint64_t value) {
    _cash += value;
    return _cash;
}

uint64_t Player::cash() const {
    return _cash;
}

void Player::set_hand(const std::pair<Card, Card> &cards) {
    _hand = cards;
}

const std::pair<Card, Card> &Player::hand() const {
    return _hand;
}

std::ostream &operator<<(std::ostream &os, const Player &player) {
    os << "P[ Cash: " << player._cash << " | Hand: " << player._hand.first << " "
       << player._hand.second << " ]";
    return os;
}

} // namespace poker
