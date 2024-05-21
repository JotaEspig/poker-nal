/**
 * \file card.hpp
 * \brief Card struct
 * \author João Vitor Espig (JotaEspig)
 * \date May 17, 2024
 * \version May 17, 2024
 **/
#pragma once

#include <ostream>

namespace poker {

/**
 * \brief Card struct
 * \author João Vitor Espig (JotaEspig)
 * \date May 17, 2024
 * \version May 17, 2024
 **/
struct Card {
    /**
     * \brief Card Suit enum
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     **/
    enum class Suit { Invalid = 0, Diamonds, Spades, Hearts, Clubs };
    /**
     * \brief Card Number enum
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     **/
    enum class Number {
        Invalid = 0,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King,
        Ace
    };

    /** Card number **/
    Number number;
    /** Card suit **/
    Suit suit;

    /**
     * \brief Default constructor
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     **/
    Card();
    /**
     * \brief Constructor that initializes number and suit
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \param number - card number
     * \param suit - card suit
     **/
    Card(Number number, Suit suit);

    /**
     * \brief operator<< overload
     * \author João Vitor Espig (JotaEspig)
     * \date May 17, 2024
     * \version May 17, 2024
     * \param os - ostream
     * \param card - card to print
     * \return ostream
     **/
    friend std::ostream &operator<<(std::ostream &os, const Card &card);
};

/**
 * \brief operator< overload
 * \author João Vitor Espig (JotaEspig)
 * \date May 21, 2024
 * \version May 21, 2024
 * \param first - first card
 * \param second - second card
 * \return bool
 **/
bool operator<(const Card &first, const Card &second);
/**
 * \brief operator<< overload
 * \author João Vitor Espig (JotaEspig)
 * \date May 17, 2024
 * \version May 17, 2024
 * \param os - ostream
 * \param suit - card suit to print
 * \return ostream
 **/
std::ostream &operator<<(std::ostream &os, const Card::Suit &suit);
/**
 * \brief operator<< overload
 * \author João Vitor Espig (JotaEspig)
 * \date May 17, 2024
 * \version May 17, 2024
 * \param os - ostream
 * \param number - card number to print
 * \return ostream
 **/
std::ostream &operator<<(std::ostream &os, const Card::Number &number);

} // namespace poker
