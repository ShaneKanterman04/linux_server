//
// Created by shane-laptop on 3/3/25.
//

#include "../include/Tcp_server.h"
#include "../include/Tcp_server.h"

#include <iostream>
#include <ostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace http {
    Tcp_server::Tcp_server(int port) {
        startServer();
    }
    Tcp_server::~Tcp_server() {
        close(m_socket);
        exit(0);
    }

    int Tcp_server::startServer() {
        std::cout << "Starting server" << std::endl;
        m_socket = socket(AF_INET, SOCK_STREAM, 0);

        if (m_socket < 0)
        {
            exitWithError("Cannot create socket");
            return 1;
        }
        std::cout << "Socket created" << std::endl;
        return 0;
    }

    void log(const std::string &message) {
        std::cout << message << std::endl;
    }

    void exitWithError(const std::string &errorMessage) {
        log("ERROR: " + errorMessage);
        exit(1);
    }

}
