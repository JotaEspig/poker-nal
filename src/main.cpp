#include <iostream>
#include <memory>

#include "game.hpp"
#include "player.hpp"

int main() {
    using namespace poker;

    Game g;
    for (int i = 0; i < 4; ++i)
        g.add_player(Player::make_shared());
    g.init_new_round();
    g.players()[0]->fold();
    g.players()[2]->fold();
    g.DEBUG(std::cout);
    std::cout << std::endl;

    for (int i = 0; i < 4; ++i)
        g.next_stage();
    auto win = g.who_wins();
    if (win != nullptr) {
        std::cout << "Vencedor: " << *(win->player) << std::endl;
        std::cout << static_cast<int>(win->combination) << std::endl;
    }
    else
        std::cout << "No one wins at this stage\n";

    for (int i = 0; i < 4; ++i)
        std::cout << "i: " << i << " - " << g.next_player_idx(i) << std::endl;

    g.finish_round();

    return 0;
}
