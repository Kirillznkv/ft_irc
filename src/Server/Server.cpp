#include "Server.hpp"

Server::Server() {} //todo: create object with port already

Server::~Server() {}


void    Server::createConnection() {

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        std::cout << "Error: socket\n";
    struct sockaddr_in addr;
    addr.sin_family = AF_UNIX;
    addr.sin_port = port; //INNADDR_ANY??
    addr.sin_addr = htons(ipAddr);
    bind()
}