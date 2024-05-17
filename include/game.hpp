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
    /**
     * \brief Player on the game
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     **/
    struct PlayerOnGame {
        /** Player obj **/
        std::shared_ptr<Player> player;
        /** is playing in the current round **/
        bool is_on_game_round;

        /**
         * \brief Fold
         * \author João Vitor Espig (JotaEspig)
         * \date May 17, 2024
         * \version May 17, 2024
         *
         * is_on_game_round is set to false
         **/
        void fold();
    };

    /** Defines the stages of a game round **/
    enum class Stage { PREFLOP = 0, FLOP, TURN, RIVER, SHOWDOWN };

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
    void init();
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
     * \brief Add player to the game table (plays just on next round)
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     **/
    void add_player(std::shared_ptr<Player> player);
    /**
     * \brief Count players with is_on_game_round = true
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \return Amount of players playing in round
     **/
    std::size_t players_playing_count() const;
    /**
     * \brief Gets table size
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \returns amount of player on table
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
    std::vector<PlayerOnGame> players() const;

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
    std::vector<PlayerOnGame> _players;
};

} // namespace poker
