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

    g.DEBUG(std::cout);
    std::cout << std::endl;

    g.finish_round();
    g.init_new_round();
    auto p = g.get_player(0);
    p->fold();
    g.DEBUG(std::cout);
    g.next_stage();
    g.DEBUG(std::cout);
    std::cout << std::endl;

    g.finish_round();
    g.init_new_round();
    g.DEBUG(std::cout);
    std::cout << std::endl;

    return 0;
}
