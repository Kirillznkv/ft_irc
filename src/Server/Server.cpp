#include "Server.hpp"

PingData::PingData() : lastMessageTime(-1), isOnline(true) {
	pthread_mutex_init(&(this->printMutex), NULL);
}
PingData::~PingData(){
	pthread_mutex_destroy(&(this->printMutex));
}

Server::Server(unsigned short int port, std::string pass) : _port(port), _pass(pass) {
	if (_port < 1024 || _port > 49151)
		throw "Wrong port!";
	init(_port, _pass);
	std::cout << "Server will be bound to port: " << _port << std::endl;
}

Server::~Server() {}

void Server::init(unsigned short int port, std::string pass) {
	if (_conf.ok() == false)
		throw "Config is not valid";
	_requestTimeout = atoi(_conf["requestTimeout"].c_str()) * 1000;
	_responseTimeout = atoi(_conf["responseTimeout"].c_str()) * 1000;
	_maxClients = atoi(_conf["maxConnections"].c_str());
	if (_maxClients < 1 || _requestTimeout < 1 || _responseTimeout < 1)
		throw "Config is not valid";
	_pingData.reserve(_maxClients);
	std::cout << "Server initialized" << std::endl;
}

bool Server::settingUpSocket() {
	int iOptVal;
	_socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketFd < 0) {
		std::cerr<<"Error opening socket"<<std::endl;
		return false;
	}
	if (setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &iOptVal, sizeof(int)) == -1) {
		std::cerr<<"Error setting socket options"<<std::endl;
		return false;
	}
	sockaddr_in serverAddr;
	bzero((char *) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(_port);
	if (bind(_socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
		std::cerr<<"Error setting socket options"<<std::endl;
		return false;
	}
	std::cout<<"Server is listening to "<<_port<<std::endl;
	listen(_socketFd, _maxClients);
	fcntl(_socketFd, F_SETFL, O_NONBLOCK);
}

void Server::newUserConnect() {
	std::string port = accepting();
	if (port.empty())
		return ;
	fcntl(_newSocketFd, F_SETFL, O_NONBLOCK);
	User user(_newSocketFd);
	user.setRealHost(port);
	_pingData[user.getId()].socket = _newSocketFd;
	_users.push_back(user);
}

void Server::execRequest(User &user, std::string buf) {
	if (buf.find('\n') == std::string::npos)
		return ;
	if (user.isRegistered() && _pingData[user.getId()].responseWaiting == false)
		_pingData[user.getId()].restartRequest = true;
	std::vector<std::string> requests = Utils::split(buf, '\n');
	for (iter_str it = requests.begin(); it != requests.end(); ++it) {
		unsigned int code = process(user, *it);
		if (code == 3)
			;
		else if (code == 7)
			;
		else if (code == 8)
			;
	}
}

std::string Server::accepting() {
	sockaddr_in clientAddr;
	socklen_t clientLen = sizeof(clientAddr);
	_newSocketFd = accept(_socketFd, (sockaddr *) &clientAddr, &clientLen);
	if (_newSocketFd < 0) {
		std::cerr<<"Error on accepting the connection"<<std::endl;
		return "";
	}
	std::cout<<"New Client Connected, ip: " << inet_ntoa(clientAddr.sin_addr)
			<<", port: " << ntohs(clientAddr.sin_port)<<std::endl;
	return inet_ntoa(clientAddr.sin_addr);
}

void Server::readSocket() {
	for (iter_user usr = _users.begin(); usr != _users.end(); ++usr)
		if (FD_ISSET(usr->getSocketFd(), &_fdRead)) {
			char buf[512];
			bzero(&buf, 512);
			if (recv(_socketFd, &buf, 512, 0) < 0) {
				std::cerr<<"Error reading from socket"<<std::endl;
				killUser(*usr);
			}
			else
				execRequest(*usr, buf);
			break ;
		}
}

void Server::start() {
	if (settingUpSocket() == false) {
		std::cerr<<"Error on binding to port"<<std::endl;
		return ;
	}
	timeval delay;
	delay.tv_sec = 0;
	delay.tv_usec = 0;
	while (_conf.ok()) {
		FD_ZERO(&_fdRead);
		FD_SET(_socketFd, &_fdRead);
		_maxFd = _socketFd;
		for (iter_user usr = _users.begin(); usr != _users.end(); ++usr) {
			FD_SET(usr->getSocketFd(), &_fdRead);
			if (usr->getSocketFd() > _maxFd)
				_maxFd = usr->getSocketFd();
		}
		if (select(_maxFd + 1, &_fdRead, NULL, NULL, &delay) > 0) {
			if (FD_ISSET(_socketFd, &_fdRead))
				newUserConnect();
			else
				readSocket();
		}
	}
}

void Server::killUser(User &user) {

}

void Server::send(int socketFd, std::string response) {

}