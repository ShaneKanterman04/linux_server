#include "Server.h"
#include <cstdlib>

int main() {
    Server server;
    if (!server.init()) {
        std::cerr << "Server initialization failed." << std::endl;
        return EXIT_FAILURE;
    }
    server.run();
    return 0;
}
