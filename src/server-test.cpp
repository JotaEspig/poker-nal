#include <cerrno>
#include <cstring>
#include <iostream>
#include <vector>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <random>
#include <sstream>

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

int main() {
    // Socket operations return values
    int result;

    // Create server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cout << "Error on socket(): " << std::strerror(errno) << "\n";
        exit(-1);
    }

    // Set sock options
    const int reuse_addr = 1;
    result = setsockopt(
        server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(int)
    );
    if (result != 0) {
        std::cout << "Error on setsockopt(): " << std::strerror(errno) << "\n";
        exit(result);
    }

    // Define server address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind server socket
    result = bind(
        server_socket, (struct sockaddr *)&server_address,
        sizeof(server_address)
    );
    if (result != 0) {
        std::cout << "Error on bind(): " << std::strerror(errno) << "\n";
        exit(result);
    }

    // Listen to requests
    result = listen(server_socket, 5);
    if (result != 0) {
        std::cout << "Error on listen(): " << std::strerror(errno) << "\n";
        exit(result);
    }
    std::cout << "Server running\n";

    // List of clients
    std::vector<std::string> clients;

    // Handle incoming client requests
    // TODO: This needs to be changed as the server could receive more than 100
    // messages
    for (int i = 0; i < 100; ++i) {
        // Accept client connection
        struct sockaddr addr;
        socklen_t len;
        int client_socket = accept(server_socket, &addr, &len);
        std::cout << "Accepted from socket " << client_socket << "\n";

        struct sockaddr_in *addr_in = (struct sockaddr_in *)&addr;
        char *client_ip = inet_ntoa(addr_in->sin_addr);
        printf("IP address: %s\n", client_ip);

        // Receive data from client
        char buffer[1024] = {0};
        result = recv(client_socket, buffer, sizeof(buffer), 0);
        if (result == -1) {
            std::cout << "Error on recv(): " << std::strerror(errno) << "\n";
            exit(-1);
        }

        // Show data
        std::cout << "Data from client: " << buffer << "\n";

        // Check client message
        std::string response = "HTTP/1.1 200 OK\r\n";
        std::string request_message{buffer};
        if (request_message == "join_game") {
            std::cout << "Player joining game\n";

            // Generate UUID for client
            std::string uuid = generate_uuid();

            // Add to clients vector
            clients.push_back(uuid);

            // Send client his uuid
            response += uuid;
        }

        response += "\r\nchameg dma ddugly";

        // Send response
        ssize_t n = send(client_socket, response.c_str(), response.length(), 0);
        if (n == -1) {
            std::cout << "Error on send(): " << std::strerror(errno) << "\n";
        }

        // Close client socket
        result = close(client_socket);
        if (result != 0) {
            std::cout << "Error on close(): " << std::strerror(errno) << "\n";
        }
    }

    // Close server socket
    result = close(server_socket);
    if (result != 0) {
        std::cout << "Error on close(): " << std::strerror(errno) << "\n";
    }

    return 0;
}