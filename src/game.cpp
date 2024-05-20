#include <algorithm>
#include <cassert>
#include <cstddef>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <utility>
#include <vector>

#include "game.hpp"
#include "utils.hpp"

/**
 * \brief Prints a single card
 */
void print_card(std::ostream &os, const poker::Card &card) {
    os << "+-----+" << "\n"
       << "| " << card.number;

    // Edge case if number is 10, which occupies two spaces
    if (card.number == poker::Card::Number::Ten) {
        os << "  |\n";
    }
    else {
        os << "   |\n";
    }

    os << "|     |" << "\n"
       << "|   " << card.suit << " |" << "\n"
       << "+-----+";
}

/**
 * \brief Prints an array of cards in the same line
 */
template <size_t N>
void print_cards(std::ostream &os, const std::array<poker::Card, N> &cards) {
    size_t i;
    // Start line
    for (i = 0; i < N; ++i) {
        os << "+-----+ ";
    }
    os << "\n";

    // Number line
    for (i = 0; i < N; ++i) {
        os << "| ";
        os << cards[i].number;

        // Edge case if number is 10, which occupies two spaces
        if (cards[i].number == poker::Card::Number::Ten) {
            os << "  | ";
        }
        else {
            os << "   | ";
        }
    }
    os << "\n";

    // White line
    for (i = 0; i < N; ++i) {
        os << "|     | ";
    }
    os << "\n";

    // Suit line
    for (i = 0; i < N; ++i) {
        os << "|   " << cards[i].suit << " | ";
    }
    os << "\n";

    // End line
    for (i = 0; i < N; ++i) {
        os << "+-----+ ";
    }
    os << "\n";
}

namespace poker {

Game::PlayerOnGame::PlayerOnGame(std::shared_ptr<Player> p) :
  player{p} {
}

void Game::PlayerOnGame::fold() {
    is_on_game_round = false;
}

bool Game::PlayerOnGame::operator<(const PlayerOnGame &other) const {
    return static_cast<int>(combination) < static_cast<int>(other.combination);
}

Game::Game() {
}

void Game::init_new_round() {
    _current_stage = static_cast<Stage>(0);
    _dealer_player_index = (_dealer_player_index + 1) % table_size();
    for (auto &e : _players) {
        e->is_on_game_round = true;
        auto hand = std::make_pair(_deck.pick_card(), _deck.pick_card());
        e->player->set_hand(hand);
    }
    for (int i = 0; i < 5; ++i) {
        _table_cards[i] = _deck.pick_card();
    }
}

void Game::reset() {
    _deck.reset();
    _table_cards.fill(Card{});
}

void Game::finish_round() {
    reset();
}

void Game::next_stage() {
    if (players_playing_count() <= 1) {
        return finish_round();
    }
    _current_stage = static_cast<Stage>(static_cast<int>(_current_stage) + 1);
}

std::shared_ptr<Game::PlayerOnGame> Game::who_wins() const {
    std::vector<std::shared_ptr<PlayerOnGame>> aux;
    for (auto p : _players) {
        if (!p->is_on_game_round)
            continue;

        std::array<Card, 7> all_cards;
        for (int i = 0; i < 5; ++i)
            all_cards[i] = _table_cards[i];
        all_cards[5] = p->player->hand().first;
        all_cards[6] = p->player->hand().second;
        /*
        if (is_royal_flush(all_cards))
            p->combination = Combination::ROYAL_FLUSH;
        else if (is_straight_flush(all_cards))
            p->combination = Combination::STRAIGHT_FLUSH;
        else if (is_four_of_a_kind(all_cards))
            p->combination = Combination::FOUR_OF_A_KIND;
        else if (is_fullhouse(all_cards))
            p->combination = Combination::FULLHOUSE;
        else if (is_flush(all_cards))
            p->combination = Combination::FLUSH;
        else if (is_straight(all_cards))
            p->combination = Combination::STRAIGHT;
        else if (is_three_of_a_kind(all_cards))
            p->combination = Combination::THREE_OF_A_KIND;
        else if (is_two_pair(all_cards))
            p->combination = Combination::TWO_PAIR;
            */
        if (is_pair(all_cards)) p->combination = Combination::PAIR;
        else p->combination = Combination::HIGH;

        aux.push_back(p);
    }
    std::sort(aux.begin(), aux.end());
    return aux.front();
}

void Game::add_player(std::shared_ptr<Player> player) {
    if (table_size() >= 9) {
        throw std::out_of_range("Game table is full");
    }

    auto pog = std::make_shared<PlayerOnGame>(player);
    _players.push_back(pog);
}

std::shared_ptr<Game::PlayerOnGame> Game::get_player(size_t index) {
    assert(index < table_size());
    return _players[index];
}

std::size_t Game::players_playing_count() const {
    size_t amount = 0;
    for (auto e : _players)
        if (e->is_on_game_round)
            ++amount;

    return amount;
}

std::vector<int> Game::players_play_order() const {
    std::vector<int> v;
    for (std::size_t i = 1; i <= table_size(); ++i) {
        int index = (_dealer_player_index + i) % table_size();
        v.push_back(index);
    }
    return v;
}

std::size_t Game::table_size() const {
    return _players.size();
}

size_t Game::dealer_player_index() const {
    return _dealer_player_index;
}

Game::Stage Game::current_stage() const {
    return _current_stage;
}

std::array<Card, 5> Game::table_cards() const {
    return _table_cards;
}

std::vector<std::shared_ptr<Game::PlayerOnGame>> Game::players() const {
    return _players;
}

void Game::DEBUG(std::ostream &os) const {
    os << "=== GAME ===" << std::endl;
    os << current_stage() << std::endl;
    os << "\nTable:\n";
    print_cards(os, table_cards());

    // Unrevealed card
    //
    // os << "\n"
    //    << "+-----+" << "\n"
    //    << "| ♦ ♦ |" << "\n"
    //    << "| ♦ ♦ |" << "\n"
    //    << "| ♦ ♦ |" << "\n"
    //    << "+-----+" << "\n";

    os << "\nPlayers:";
    for (auto p : players()) {
        // Print player info
        os << "\nP[ Cash: " << p->player->cash()
           << " | Is on round: " << p->is_on_game_round << " ]\n";

        // Print hand
        auto hand = p->player->hand();
        std::array<Card, 2> hand_arr = {hand.first, hand.second};
        print_cards(os, hand_arr);
    }
    os << std::endl;
    os << "Dealer Index: " << dealer_player_index() << std::endl;
    for (int i : players_play_order()) {
        os << i << ", ";
    }
    os << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Game::Stage &stage) {
    switch (stage) {
    case Game::Stage::PREFLOP:
        os << "PREFLOP";
        break;
    case Game::Stage::FLOP:
        os << "FLOP";
        break;
    case Game::Stage::TURN:
        os << "TURN";
        break;
    case Game::Stage::RIVER:
        os << "RIVER";
        break;
    case Game::Stage::SHOWDOWN:
        os << "SHOWDOWN";
        break;
    }
    return os;
}

} // namespace poker
