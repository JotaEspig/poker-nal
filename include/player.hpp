/**
 * \file player.hpp
 * \brief Player class
 * \author João Vitor Espig (JotaEspig)
 * \date May 17, 2024
 * \version May 17, 2024
 **/
#pragma once

#include <cstdint>
#include <utility>

#include "card.hpp"

namespace poker {

/**
 * \brief Player class
 * \author João Vitor Espig (JotaEspig)
 * \date May 17, 2024
 * \version May 17, 2024
 **/
class Player {
public:
    /**
     * \brief Default constructor
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     **/
    Player();
    /**
     * \brief Constructor that initializes player's hand
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * param cards - pair of cards
     **/
    Player(const std::pair<Card, Card> &cards);

    /**
     * \brief Checks if player can bet that value
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \param value - value of the bet
     * \return true or false
     **/
    bool can_bet(uint64_t value);
    /**
     * \brief bets the value
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \param value - value of the bet
     * \return updated player's cash
     **/
    uint64_t bet(uint64_t value);
    /**
     * \brief receives the value
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \param value - value
     * \return updated player's cash
     **/
    uint64_t receive(uint64_t value);

    /**
     * \brief _cash getter
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \return player's cash
     **/
    uint64_t cash() const;
    /**
     * \brief _hand getter
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \param cards - pair of cards
     **/
    void set_hand(const std::pair<Card, Card> &cards);
    /**
     * \brief _hand getter
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \return player's hand
     **/
    const std::pair<Card, Card> &hand() const;

    /**
     * \brief operator<< overload
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \param os - ostream
     * \param player - player to print
     * \return ostream
     **/
    friend std::ostream &operator<<(std::ostream &os, const Player &player);

private:
    /** Player's cash **/
    uint64_t _cash;
    /** Player's hand **/
    std::pair<Card, Card> _hand;
};

} // namespace poker
