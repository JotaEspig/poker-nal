#include <iostream>
#include <memory>

#include "game.hpp"
#include "player.hpp"

int main() {
    using namespace poker;

    Game g;
    for (int i = 0; i < 6; ++i)
        g.add_player(Player::make_shared());
    g.init_new_round();
    g.players()[0]->fold();
    g.players()[2]->fold();
    g.DEBUG(std::cout);
    std::cout << std::endl;

    std::cout << *(g.who_wins()->player) << std::endl;

    for (int i = 0; i < 6; ++i)
        std::cout << "i: " << i << " - " << g.next_player_idx(i) << std::endl;

    return 0;
}
