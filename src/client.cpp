#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

#include <random>

#include "client.hpp"

#define DEFAULT_PORT 8080

namespace poker {

Client::Client() {
}

Client::Client(int port) :
  port{port} {
    // Create client socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        std::cout << "Error on client socket(): " << std::strerror(errno) << "\n";
        exit(-1);
    }

    // Define client address
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(port);
    client_address.sin_addr.s_addr = INADDR_ANY;

    int result = connect(
        client_fd, (struct sockaddr *)&client_address, sizeof(client_address)
    );
    if (result != 0) {
        std::cout << "Error on client connect(): " << std::strerror(errno) << "\n";
        exit(-1);
    }
    std::cout << "Client running\n";
}

void Client::start() {
    // Send initial message, asking for
    std::string uuid = send_message("join_game");
    if (uuid.length() > 0) {
        std::cout << "Got UUID: " << uuid << "\n";
    }
    else {
        std::cout << "join_game message failed\n";
    }

    // Main looop
    std::string line;
    while (true) {
        std::cout << "Send message to server:";
        std::getline(std::cin, line);

        std::string response = send_message(line);
        std::cout << "Got message:\n" << response << "\n";
    }

    // Close client_fd
    int result = close(client_fd);
    if (result != 0) {
        std::cout << "Error on client close(): " << std::strerror(errno)
                  << "\n";
    }
}

std::string Client::send_message(const std::string &message) const {
    // TODO: Standardize message type (json, whatever, ...)

    // Send message
    ssize_t bytes_send = send(client_fd, message.c_str(), message.length(), 0);
    if (bytes_send == -1L) {
        std::cout << "Error on client send(): " << std::strerror(errno) << "\n";
        return "";
    }

    // Receive message
    char buffer[10001] = {0};
    ssize_t message_len = recv(client_fd, buffer, sizeof(buffer), 0);
    if (message_len == -1) {
        std::cout << "Error on client recv(): " << std::strerror(errno) << "\n";
        return "";
    }

    return std::string{buffer};
}

} // namespace poker