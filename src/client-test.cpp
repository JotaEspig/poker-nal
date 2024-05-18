#include <iostream>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char **argv) {
    // Set client name
    std::string client_name = "client";
    if (argc == 2) {
        client_name = argv[1];
    }

    // Create client socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define server address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Connect client to server
    connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    // Send message
    std::string message = "Hello from client \"" + client_name + "\"!";
    send(client_socket, message.c_str(), message.length(), 0);

    // Close client socket
    close(client_socket);

    return 0;
}