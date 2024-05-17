#include <iostream>

#include "game.hpp"
#include "player.hpp"

int main() {
    using namespace poker;

    Game g;
    for (int i = 0; i < 6; ++i)
        g.add_player(Player::make_shared());
    g.init();

    g.DEBUG(std::cout);

    return 0;
}
