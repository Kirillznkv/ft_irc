#include "Server.hpp"

Server::Server() {} //todo: create object with port already

Server::~Server() {}


void    Server::error(int err, std::string clarification) {
    std::cout << "Error: " << clarification << std::endl;
    exit(err);
}


void    Server::createConnection() {

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        error(0, "creation socket¬")
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = port; //INNADDR_ANY??
    addr.sin_addr = htons(ipAddr);
    bind()
}