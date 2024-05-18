#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    // Create server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define server address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind server socket
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    // Listen to requests
    int result = listen(server_socket, 0);
    if (result != 0)
    {
        std::cout << "Error on listen()\n";
        exit(result);
    }

    // Accept client connection
    for (int i = 0; i < 100; ++i)
    {
        int client_socket = accept(server_socket, nullptr, nullptr);

        // Receive data from client
        char buffer[1024] = {0};
        result = recv(client_socket, buffer, sizeof(buffer), 0);
        if (result == -1)
        {
            std::cout << "Error on recv()\n";
            exit(-1);
        }

        // Show data
        std::cout << "Data from client: " << buffer << "\n";
    }

    // Close server socket
    close(server_socket);

    return 0;
}