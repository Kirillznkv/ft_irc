#include "Server.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

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
	int fd = open("output.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (_conf.ok() == false) { // проверка везде
		std::cout<< "Error: Fail config file\n";
		return ;
	}
	User user(3);
	user.setSocketFd(fd);
	_users.push_back(user);
	Channel channel("lol", user);
	_channels.push_back(channel);
	std::string req1 = "NICK kshanti";
	std::string req2 = "PASS pass";
	std::string req3 = "USER a a a a";
	std::string req4 = "JOIN #kek";
	unsigned int code = process(user, req1);
	code = process(user, req2);
	code = process(user, req3);
	code = process(user, req2);
	code = process(user, req4);
	close(fd);
}

void Server::killUser(User &user) { user.getHost(); }
void Server::send(int socketFd, std::string response) {
	write(socketFd, response.c_str(), response.size());
}