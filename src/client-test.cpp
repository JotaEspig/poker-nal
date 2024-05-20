#include <cerrno>
#include <cstring>
#include <iostream>
#include <string>

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Socket operations return values
    int result;

    // Create client socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cout << "Error on socket(): " << std::strerror(errno) << "\n";
        exit(-1);
    }

    // Define server address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Connect client to server
    result = connect(
        client_socket, (struct sockaddr *)&server_address,
        sizeof(server_address)
    );
    if (result != 0) {
        std::cout << "Error on connect(): " << std::strerror(errno) << "\n";
    }

    for (int i = 0; i < 2; ++i) {
        // Send message
        // TODO: Standardize message type (json, whatever, ...)
        std::string message = "join_game";
        send(client_socket, message.c_str(), message.length(), 0);

        // Receive message from server
        char buffer[1024] = {0};
        ssize_t message_len = recv(client_socket, buffer, sizeof(buffer), 0);
        std::cout << "Received message with " << message_len << " bytes\n";

        if (message_len > 0) {
            std::cout << buffer << "\n";
        }
    }

    // Close client socket
    result = close(client_socket);
    if (result != 0) {
        std::cout << "Error on close(): " << std::strerror(errno) << "\n";
    }

    return 0;
}