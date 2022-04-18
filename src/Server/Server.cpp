#include "Server.hpp"

Server::Server(unsigned short int port, std::string pass) : _port(port), _pass(pass) {} //todo: create object with port already

Server::~Server() {}


void    Server::createConnection() {

    // if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    //     std::cout << "Error: socket\n";
    // struct sockaddr_in addr;
    // addr.sin_family = AF_UNIX;
    // addr.sin_port = port; //INNADDR_ANY??
    // addr.sin_addr = htons(ipAddr);
    // bind()
}

void Server::start() {
	User user(3);
	user.setId(1);
	_users.push_back(user);
	std::string req1 = "NICK kshanti";
	std::string req2 = "PASS pass";
	std::string req3 = "USER a a a a";
	int code = process(user, req1);
	int code = process(user, req2);
	int code = process(user, req3);
}