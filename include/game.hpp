/**
 * \file game.hpp
 * \brief Game class
 * \author João Vitor Espig (JotaEspig)
 * \date May 17, 2024
 * \version May 17, 2024
 **/
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <vector>

#include "deck.hpp"
#include "player.hpp"

namespace poker {

/**
 * \brief Game class
 * \author João Vitor Espig (JotaEspig)
 * \date May 17, 2024
 * \version May 17, 2024
 *
 * It means a game table
 **/
class Game {
public:
    /** Defines the stages of a game round **/
    enum class Stage { PREFLOP = 0, FLOP, TURN, RIVER, SHOWDOWN };
    /** Defines the all possible combinations of a hand **/
    enum class Combination {
        NOT_COMPUTED_YET = 0,
        HIGH,
        PAIR,
        TWO_PAIR,
        THREE_OF_A_KIND,
        STRAIGHT,
        FLUSH,
        FULLHOUSE,
        FOUR_OF_A_KIND,
        STRAIGHT_FLUSH,
        ROYAL_FLUSH
    };

    /**
     * \brief Player on the game
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     **/
    struct PlayerOnGame {
        /** player object **/
        std::shared_ptr<Player> player;
        /** is playing in the current round **/
        bool is_on_game_round = false;
        /** player hand combination **/
        Combination combination = Combination::NOT_COMPUTED_YET;

        /**
         * \brief Default constructor
         * \author João Vitor Espig (JotaEspig)
         * \date May 17, 2024
         * \version May 17, 2024
         **/
        PlayerOnGame(std::shared_ptr<Player> p);
        /**
         * \brief Fold
         * \author João Vitor Espig (JotaEspig)
         * \date May 17, 2024
         * \version May 17, 2024
         *
         * is_on_game_round is set to false
         **/
        void fold();

        bool operator<(const PlayerOnGame &other) const;
    };

    /**
     * \brief Default constructor
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     **/
    Game();

    /**
     * \brief Start the game
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     *
     * Initialize players hands
     **/
    void init_new_round();
    /**
     * \brief Resets the game
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     *
     * Reset the deck
     **/
    void reset();
    /**
     * \brief go to next stage of the round
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     **/
    void finish_round();
    /**
     * \brief go to next stage of the round
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     **/
    void next_stage();
    /**
     * \brief get the next player who must play
     * \author João Vitor Espig (JotaEspig)
     * \date May 20, 2024
     * \version May 20, 2024
     * \return a number > 0 if a player has to play yet, -1 if the stage is over
     **/
    std::int64_t next_player_idx(std::size_t idx) const;
    /**
     * \brief Check who wins in the round
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \return pointer to player who wins
     **/
    std::shared_ptr<PlayerOnGame> who_wins() const;
    /**
     * \brief Add player to the game table (plays just on next round)
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \param player - Player shared ptr
     **/
    void add_player(std::shared_ptr<Player> player);
    /**
     * \brief Gets a player at index
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \return PlayerOnGame shared pointer object
     **/
    std::shared_ptr<PlayerOnGame> get_player(size_t index);
    /**
     * \brief Count players with is_on_game_round = true
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \return Amount of players playing in round
     **/
    std::size_t players_playing_count() const;
    /**
     * \brief Gets the who plays first, second, etc...
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \return players indeces in order to play (Who has Dealer button is the
     *last to play
     **/
    std::vector<std::size_t> players_play_order() const;
    /**
     * \brief Gets table size
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \returns amount of player on table, player at idx 0 is small blind and player at idx 1 is big blind
     **/
    std::size_t table_size() const;

    /**
     * \brief _dealer_player_index getter
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \return dealer player index
     **/
    size_t dealer_player_index() const;
    /**
     * \brief _current_stage getter
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \return current stage
     **/
    Stage current_stage() const;
    /**
     * \brief _table_cards getter
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \return table cards
     **/
    std::array<Card, 5> table_cards() const;
    /**
     * \brief _players getter
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \return players
     **/
    std::vector<std::shared_ptr<PlayerOnGame>> players() const;

    void DEBUG(std::ostream &os) const;

private:
    /** player index at _players who is the dealer **/
    size_t _dealer_player_index = 0;
    /** current stage of the round **/
    Stage _current_stage;
    /** deck **/
    Deck _deck;
    /** table cards **/
    std::array<Card, 5> _table_cards;
    /** Player on the table **/
    std::vector<std::shared_ptr<PlayerOnGame>> _players;
};

std::ostream &operator<<(std::ostream &os, const Game::Stage &stage);

} // namespace poker
