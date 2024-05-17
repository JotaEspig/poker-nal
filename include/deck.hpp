/**
 * \file deck.hpp
 * \brief Deck class
 * \author João Vitor Espig (JotaEspig)
 * \date May 17, 2024
 * \version May 17, 2024
 **/
#pragma once

#include <ostream>
#include <vector>

#include "card.hpp"

namespace poker {

/**
 * \brief Deck class
 * \author João Vitor Espig (JotaEspig)
 * \date May 17, 2024
 * \version May 17, 2024
 **/
class Deck {
public:
    /**
     * \brief Default constructor
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     **/
    Deck();

    /**
     * \brief Restarts deck
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     **/
    void restart();
    /**
     * \brief shuffle cards
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     **/
    void shuffle();
    /**
     * \brief pick a card from the top of the "stack"
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \return picked card
     **/
    Card pick_card();
    /**
     * \brief _cards getter
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \return deck cards
     **/
    const std::vector<Card> &cards() const;

    /**
     * \brief operator<< overload
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \param os - ostream
     * \param deck - deck to print
     * \return ostream
     **/
    friend std::ostream &operator<<(std::ostream &os, const Deck &deck);

private:
    /** Deck cards **/
    std::vector<Card> _cards;

    /**
     * \brief generates the deck cards
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     **/
    void generate_deck();
};

} // namespace poker
