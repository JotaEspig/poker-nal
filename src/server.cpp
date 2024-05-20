#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

#include <random>

#include "server.hpp"

#define DEFAULT_PORT 8080

namespace poker {
/** For socket SO_REUSEADDR option */
static const int reuse_addr = 1;

// TODO: If this is going to be used, move it to a separate file
std::string generate_uuid() {
    static std::random_device dev;
    static std::mt19937 rng{dev()};
    std::uniform_int_distribution<int> dist{0, 15};

    const char *v = "0123456789abcdef";
    const bool dash[] = {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0};

    std::string res;
    for (int i = 0; i < 16; ++i) {
        if (dash[i]) {
            res += "-";
        }
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}

Server::Server() {
}

Server::Server(int port) :
  port{port} {
    // Create server socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cout << "Error on socket(): " << std::strerror(errno) << "\n";
        exit(-1);
    }

    // Set sock options
    int result;
    result = setsockopt(
        server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(int)
    );
    if (result != 0) {
        std::cout << "Error on setsockopt(): " << std::strerror(errno) << "\n";
        exit(result);
    }

    // Define server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind server socket
    result = bind(
        server_fd, (struct sockaddr *)&server_address, sizeof(server_address)
    );
    if (result != 0) {
        std::cout << "Error on bind(): " << std::strerror(errno) << "\n";
        exit(result);
    }

    // Listen to requests
    result = listen(server_fd, 5);
    if (result != 0) {
        std::cout << "Error on listen(): " << std::strerror(errno) << "\n";
        exit(result);
    }
    std::cout << "Server running\n";
}

void Server::start() {
    std::vector<int> clients;

    while (true) {
        // Accept client connection
        struct sockaddr addr;
        socklen_t len;
        int client_socket = accept(server_fd, &addr, &len);

        // Get client IP address
        struct sockaddr_in *addr_in = (struct sockaddr_in *)&addr;
        char *client_ip = inet_ntoa(addr_in->sin_addr);
        std::cout << "IP address: " << client_ip << "\n";

        // Receive data from client
        int result;
        char buffer[1024] = {0};
        result = recv(client_socket, buffer, sizeof(buffer), 0);
        if (result == -1) {
            std::cout << "Error on recv(): " << std::strerror(errno) << "\n";
            exit(-1);
        }

        // Show data
        std::cout << "Data from client: " << buffer << "\n";

        // Check client message
        std::string response;
        std::string request_message{buffer};
        if (request_message == "join_game") {
            std::cout << "Player joining game\n";

            // Generate UUID for client
            std::string uuid = generate_uuid();

            // Send client his uuid
            response = uuid;
        }

        // Send response
        ssize_t n = send(client_socket, response.c_str(), response.length(), 0);
        if (n == -1) {
            std::cout << "Error on send(): " << std::strerror(errno) << "\n";
        }

        // Close client socket
        // result = close(client_socket);
        // if (result != 0) {
        //     std::cout << "Error on close(): " << std::strerror(errno) << "\n";
        // }

        clients.push_back(client_socket);
        std::cout << "Clients: ";
        for (auto &c : clients) {
            std::cout << c << ", ";
        }
        std::cout << "\n";

        if (clients.size() == 4UL) {
            std::cout << "Sending message to all clients\n";
            const char* msg = "testing\n";
            for (size_t i = 0; i < clients.size(); ++i) {
                send(clients[i], msg, strlen(msg), 0);
            }
        }
    }
}

} // namespace poker