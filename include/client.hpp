/**
 * \file client.hpp
 * \brief Client class
 * \author Mickael Reichert (mickelrei)
 * \date May 20, 2024
 * \version May 20, 2024
 **/
#pragma once

#include <netinet/in.h>
#include <ostream>

namespace poker {

/**
 * \brief Client class
 * \author Mickael Reichert (mickaelrei)
 * \date May 20, 2024
 * \version May 20, 2024
 **/
class Client {
public:
    /**
     * \brief Default constructor
     * \author Mickael Reichert (mickaelrei)
     * \date May 20, 2024
     * \version May 20, 2024
     **/
    Client();
    /**
     * \brief Constructor that initializes with port
     * \author Mickael Reichert (mickaelrei)
     * \date May 20, 2024
     * \version May 20, 2024
     * \param port - client port
     **/
    Client(int port);

    /**
     * \brief Start client
     * \author Mickael Reichert (mickaelrei)
     * \date May 20, 2024
     * \version May 20, 2024
    */
    void start();

    /**
     * \brief Sends a message to the server
     * \author Mickael Reichert (mickaelrei)
     * \date May 20, 2024
     * \version May 20, 2024
     * \return response from server
    */
    std::string send_message(const std::string &message) const;

    /**
     * \brief operator<< overload
     * \author Mickael Reichert (mickaelrei)
     * \date May 20, 2024
     * \version May 20, 2024
     * \param os - ostream
     * \param client - client to print
     * \return ostream
     **/
    friend std::ostream &operator<<(std::ostream &os, const Client &player);

private:
    /** Client's port **/
    int port;

    /** Client's socket fd */
    int client_fd;

    /** Client address */
    sockaddr_in client_address;
};

} // namespace poker
