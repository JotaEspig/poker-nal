/**
 * \file server.hpp
 * \brief Server class
 * \author Mickael Reichert (mickelrei)
 * \date May 19, 2024
 * \version May 19, 2024
 **/
#pragma once

#include <netinet/in.h>
#include <ostream>

namespace poker {

/**
 * \brief Server class
 * \author Mickael Reichert (mickaelrei)
 * \date May 19, 2024
 * \version May 19, 2024
 **/
class Server {
public:
    /**
     * \brief Default constructor
     * \author Mickael Reichert (mickaelrei)
     * \date May 19, 2024
     * \version May 19, 2024
     **/
    Server();
    /**
     * \brief Constructor that initializes player's cash
     * \author Mickael Reichert (mickaelrei)
     * \date May 19, 2024
     * \version May 19, 2024
     * \param port - server port
     **/
    Server(int port);

    /**
     * \brief Start server
     * \author Mickael Reichert (mickaelrei)
     * \date May 19, 2024
     * \version May 19, 2024
    */
    void start();

    /**
     * \brief operator<< overload
     * \author Mickael Reichert (mickaelrei)
     * \date May 19, 2024
     * \version May 19, 2024
     * \param os - ostream
     * \param server - server to print
     * \return ostream
     **/
    friend std::ostream &operator<<(std::ostream &os, const Server &player);

private:
    /** Server's port **/
    int port;

    /** Server's socket fd */
    int server_fd;

    /** Server address */
    sockaddr_in server_address;
};

} // namespace poker
