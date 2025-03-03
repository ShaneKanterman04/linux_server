//
// Created by shane-laptop on 3/3/25.
//

#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#include <string>


namespace http {
    class Tcp_server {
    public:
        Tcp_server(int port);
        ~Tcp_server();

        int startServer();

        void log(const std::string &message);

        void exitWithError(const std::string &errorMessage);


    private:
        int port;
        int m_socket;

    };
}




#endif //TCP_SERVER_H
