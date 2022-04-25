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
	std::string req1 = "NICK kshanti";
	std::string req2 = "PASS pass";
	std::string req3 = "USER a a a a";
	std::string req4 = "JOIN #kek";
	std::string req5 = "JOIN #lol";
	std::string req6 = "JOIN &myFirstChannel";
	std::string req7 = "JOIN &mySecondChannel 123";
	std::string req8 = "LIST";
	std::string req9 = "NAMES";
	std::string req10 = "NAMES kshanti";
	std::string req11 = "PART #lol,#kek";
	std::string r1 = "OPER kshanti 123";
	std::string r2 = "MODE #kek +p";
	std::string r3 = "MODE #kek -p";
	std::string r4 = "WHO kshanti";
	std::string r5 = "WHOIS kshanti";
	unsigned int code = process(_users[0], req1);
	code = process(_users[0], req2);
	code = process(_users[0], req3);
	code = process(_users[0], req2);
	code = process(_users[0], req4);
	code = process(_users[0], req5);
	code = process(_users[0], req6);
	code = process(_users[0], req7);
	code = process(_users[0], req8);
	code = process(_users[0], r1);
	code = process(_users[0], r2);
	code = process(_users[0], r3);
	code = process(_users[0], req9);
	code = process(_users[0], req10);
	code = process(_users[0], req11);
	code = process(_users[0], req8);
	code = process(_users[0], r4);
	code = process(_users[0], r5);
	close(fd);
	std::cout<<"\nchannels: ";
	for (iter_channel i = _channels.begin(); i != _channels.end(); ++i)
		std::cout<<i->getChannelName()<<" ";
	std::cout<<"\nusers: ";
	for (iter_user i = _users.begin(); i != _users.end(); ++i)
		std::cout<<i->getNickName()<<" ";
	std::cout<<std::endl;
}

void Server::killUser(User &user) { user.getHost(); }
void Server::send(int socketFd, std::string response) {
	write(socketFd, response.c_str(), response.size());
}