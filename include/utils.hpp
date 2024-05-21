#pragma once

#include <array>
#include <utility>

#include "card.hpp"
#include "game.hpp"

namespace poker {

bool is_pair(std::array<Card, 7> all_cards);
bool is_two_pair(std::array<Card, 7> all_cards);
bool is_three_of_a_kind(std::array<Card, 7> all_cards);
bool is_straight(std::array<Card, 7> all_cards);
bool is_flush(std::array<Card, 7> all_cards);
bool is_fullhouse(std::array<Card, 7> all_cards);
bool is_four_of_a_kind(std::array<Card, 7> all_cards);
bool is_straight_flush(std::array<Card, 7> all_cards);
bool is_royal_flush(std::array<Card, 7> all_cards);

void print_card(std::ostream &os, const Card &card, const bool &revealed);
void print_game_stage(std::ostream &os, const Game::Stage &stage, const std::array<Card, 5> &cards);
void print_player_hand(std::ostream &os, const std::pair<Card, Card> &cards);

} // namespace poker
