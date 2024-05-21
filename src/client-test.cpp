#include <iostream>

#include "client.hpp"

int main() {
    poker::Client client{8080};
    client.start();
}