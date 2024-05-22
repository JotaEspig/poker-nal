#include <array>
#include <cstddef>

#include "card.hpp"
#include "utils.hpp"

namespace poker {

bool is_pair(std::array<Card, 7> all_cards) {
    for (std::size_t i = 0; i < 7; ++i) {
        Card c1 = all_cards[i];
        for (std::size_t j = 0; j < 7; ++j) {
            if (i == j)
                continue;

            Card c2 = all_cards[j];
            if (c1.number == c2.number)
                return true;
        }
    }

    return false;
}

bool is_two_pair(std::array<Card, 7> all_cards) {
    bool pairs[2] = {false, false};
    Card::Number nums[2] = {Card::Number::Invalid, Card::Number::Invalid};
    for (int aux = 0; aux < 2; ++aux) {
        for (std::size_t i = 0; i < 7; ++i) {
            Card c1 = all_cards[i];
            if (nums[0] == c1.number)
                continue;

            for (std::size_t j = 0; j < 7; ++j) {
                if (i == j)
                    continue;

                Card c2 = all_cards[j];
                if (c1.number == c2.number) {
                    nums[aux] = c1.number;
                    pairs[aux] = true;
                    break;
                }
            }
            if (pairs[aux])
                break;
        }
    }
    return pairs[0] && pairs[1];
}

bool is_three_of_a_kind(std::array<Card, 7> all_cards) {
    return false;
}

bool is_straight(std::array<Card, 7> all_cards) {
    return false;
}

bool is_flush(std::array<Card, 7> all_cards) {
    return false;
}

bool is_fullhouse(std::array<Card, 7> all_cards) {
    return false;
}

bool is_four_of_a_kind(std::array<Card, 7> all_cards) {
    return false;
}

bool is_straight_flush(std::array<Card, 7> all_cards) {
    return false;
}

bool is_royal_flush(std::array<Card, 7> all_cards) {
    return false;
}

void print_card(std::ostream &os, const Card &card, const bool &revealed) {
    if (!revealed) {
        os << "+-----+" << "\n"
           << "| ♦ ♦ |" << "\n"
           << "| ♦ ♦ |" << "\n"
           << "| ♦ ♦ |" << "\n"
           << "+-----+" << "\n";
        return;
    }

    os << "+-----+" << "\n"
       << "| ";
    os << card.number;

    // Edge case if number is 10, which occupies two spaces
    if (card.number == Card::Number::Ten) {
        os << "  |\n";
    }
    else {
        os << "   |\n";
    }

    os << "|     |" << "\n"
       << "|   " << card.suit << " |" << "\n"
       << "+-----+";
}

void print_game_stage(
    std::ostream &os, const Game::Stage &stage, const std::array<Card, 5> &cards
) {
    (void)stage;

    std::size_t i;
    // Start line
    for (i = 0; i < 5; ++i) {
        os << "+-----+ ";
    }
    os << "\n";

    // Number line
    for (i = 0; i < 5; ++i) {
        os << "| ";
        os << cards[i].number;

        // Edge case if number is 10, which occupies two spaces
        if (cards[i].number == Card::Number::Ten) {
            os << "  | ";
        }
        else {
            os << "   | ";
        }
    }
    os << "\n";

    // White line
    for (i = 0; i < 5; ++i) {
        os << "|     | ";
    }
    os << "\n";

    // Suit line
    for (i = 0; i < 5; ++i) {
        os << "|   " << cards[i].suit << " | ";
    }
    os << "\n";

    // End line
    for (i = 0; i < 5; ++i) {
        os << "+-----+ ";
    }
    os << "\n";
}

void print_player_hand(std::ostream &os, const std::pair<Card, Card> &cards) {
    // Start line
    os << "+-----+ +-----+\n";

    // Number line
    os << "| ";
    os << cards.first.number;

    // Edge case if number is 10, which occupies two spaces
    if (cards.first.number == Card::Number::Ten) {
        os << "  | ";
    }
    else {
        os << "   | ";
    }

    os << "| ";
    os << cards.second.number;

    // Edge case if number is 10, which occupies two spaces
    if (cards.second.number == Card::Number::Ten) {
        os << "  |\n";
    }
    else {
        os << "   |\n";
    }

    // White line
    os << "|     |\n";

    // Suit line
    os << "|   " << cards.first.suit << " | ";
    os << "|   " << cards.second.suit << " |\n";

    // End line
    os << "+-----+ +-----+\n";
}

} // namespace poker
