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

    g.finish_round();
    g.init_new_round();
    std::shared_ptr<Game::PlayerOnGame> p = g.get_player(0);
    std::cout << p << std::endl;
    p->fold();
    g.DEBUG(std::cout);

    g.finish_round();
    g.init_new_round();
    g.DEBUG(std::cout);

    return 0;
}
