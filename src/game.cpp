#include <cassert>
#include <cstddef>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <utility>
#include <vector>

#include "game.hpp"

namespace poker {

Game::PlayerOnGame::PlayerOnGame(std::shared_ptr<Player> p) :
  player{p} {
}

void Game::PlayerOnGame::fold() {
    is_on_game_round = false;
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

std::array<Card, 5> Game::table_cards() const {
    return _table_cards;
}

std::vector<std::shared_ptr<Game::PlayerOnGame>> Game::players() const {
    return _players;
}

void Game::DEBUG(std::ostream &os) const {
    os << "=== GAME ===\n" << std::endl;
    for (auto c : table_cards()) {
        os << c << " , ";
    }
    os << std::endl;
    for (auto p : players()) {
        os << *(p->player) << "-" << p->is_on_game_round << " , ";
    }
    os << std::endl;
    os << "Dealer Index: " << dealer_player_index() << std::endl;
    for (int i : players_play_order()) {
        os << i << ", ";
    }
    os << std::endl;
}

} // namespace poker
