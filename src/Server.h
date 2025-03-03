#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

class Server {
private:
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen;
    const char* response;
    char buffer[1024];

public:
    // Constructor and Destructor
    Server();
    ~Server();

    // Initializes the socket, sets options, binds and listens
    bool init();

    // Accepts connections and spawns a new thread for each connection
    void run();
};

#endif // SERVER_H
