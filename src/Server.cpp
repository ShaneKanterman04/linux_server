#include "Server.h"
#include <cstdlib>
#include <thread>   // Include the thread library

// Helper function to handle a client connection on a separate thread.
void handle_client(int client_socket, const char* response) {
    char buffer[1024] = {0};  // Local buffer for this thread
    int valread = read(client_socket, buffer, sizeof(buffer));
    if (valread < 0) {
        perror("read failed");
    } else {
        std::cout << "Received request:" << std::endl;
        std::cout << buffer << std::endl;
    }
    send(client_socket, response, strlen(response), 0);
    std::cout << "Response sent" << std::endl;
    close(client_socket);
}

Server::Server()
    : server_fd(0),
      new_socket(0),
      addrlen(sizeof(address)),
      response("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!")
{
    // Clear the buffer (not used in threaded code)
    memset(buffer, 0, sizeof(buffer));
}

Server::~Server() {
    // Close the listening socket
    close(server_fd);
}

bool Server::init() {
    int opt = 1;
    // Create socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        return false;
    }
    // Set socket options to allow reuse of address and port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)) != 0) {
        perror("setsockopt");
        return false;
    }
    // Configure the address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind the socket to the specified IP and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return false;
    }

    // Mark the socket as passive to accept incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        return false;
    }
    std::cout << "Server listening on port 8080..." << std::endl;
    return true;
}

void Server::run() {
    while (true) {
        // Accept an incoming connection
        int client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            perror("accept failed");
            continue;  // Continue to the next iteration if accept fails
        }
        // Spawn a new thread to handle the client connection
        std::thread t(handle_client, client_socket, response);
        t.detach();  // Detach the thread to allow it to run independently
    }
}
