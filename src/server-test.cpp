#include <iostream>

#include "server.hpp"

int main() {
    poker::Server server{8080};
    server.start();

    return 0;
}