#include "Server.hpp"

Server::PingData::PingData() : lastMessageTime(-1), isOnline(true) {
}
Server::PingData::~PingData(){
}

Server::Server(unsigned short int port, std::string pass) : _port(port), _pass(pass) {
	if (_port < 1024 || _port > 49151)
		throw "Wrong port!";
	init();
	if (settingUpSocket() == false)
		throw "Error on binding to port";
	std::cout << "Server will be bound to port: " << _port << std::endl;
}

Server::~Server() {}

void Server::init() {
	if (_conf.ok() == false)
		throw "Config is not valid";
	_requestTimeout = atoi(_conf["requestTimeout"].c_str()) * 1000;
	_responseTimeout = atoi(_conf["responseTimeout"].c_str()) * 1000;
	_maxClients = atoi(_conf["maxConnections"].c_str());
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
	return true;
}

void Server::newUserConnect() {
	if (_users.size() == (size_t)_maxClients) {
		std::cerr<<"Error users limit"<<std::endl;
		return ;
	}
	std::string port = accepting();
	if (port.empty())
		return ;
	fcntl(_newSocketFd, F_SETFL, O_NONBLOCK);
	User user(_newSocketFd);
	user.setRealHost(port);
	_pingData.push_back(PingData());
	_pingData[user.getId()].serverName = _conf["name"];
	_pingData[user.getId()].socket = _newSocketFd;
	_pingData[user.getId()].requestTimeout = _requestTimeout;
	_pingData[user.getId()].responseTimeout = _responseTimeout;
	_pingData[user.getId()].disconnect = false;
	_users.push_back(user);
}

void Server::execRequest(User &user, std::string buf) {
	while (buf.find("\r\n") != std::string::npos)
		buf.replace(buf.find("\r\n"), 2, "\n");
	if (buf.find('\n') == std::string::npos)
		return ;
	if (user.isRegistered() && _pingData[user.getId()].responseWaiting == false)
		_pingData[user.getId()].restartRequest = true;
	std::vector<std::string> requests = Utils::split(buf, '\n');
	for (iter_str it = requests.begin(); it != requests.end(); ++it)
		process(user, *it);
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
			if (recv(usr->getSocketFd(), &buf, 512, 0) <= 0) {
				std::cerr<<"Error reading from socket"<<std::endl;
				killUser(*usr);
			}
			else if (_pingData[usr->getId()].disconnect == true)
				killUser(*usr);
			else
				execRequest(*usr, buf);
			break ;
		}
}

void Server::start() {
	while (_conf.ok()) {
		FD_ZERO(&_fdRead);
		FD_SET(_socketFd, &_fdRead);
		_maxFd = _socketFd;
		for (iter_user usr = _users.begin(); usr != _users.end(); ++usr) {
			FD_SET(usr->getSocketFd(), &_fdRead);
			if (usr->getSocketFd() > _maxFd)
				_maxFd = usr->getSocketFd();
		}
		if (select(_maxFd + 1, &_fdRead, NULL, NULL, NULL) > 0) {
			if (FD_ISSET(_socketFd, &_fdRead))
				newUserConnect();
			else
				readSocket();
		}
	}
}

void Server::kickUserFromChannel(User &user, iter_channel channel) {
	for (iter_user usr = channel->getUsers().begin(); usr != channel->getUsers().end(); ++usr)
		Server::sendP2PMsg(user, *usr, "QUIT", "Client exited");
	if (Utils::isUserExist(channel->getOpers(), user.getNickName())) {
		if (channel->getOpers().size() == 1 && channel->getUsers().size() == 1)
			_channels.erase(Utils::findChannel(_channels, channel->getChannelName()));
		else if (channel->getOpers().size() == 1){
			iter_user newOper;
			for (newOper = channel->getUsers().begin(); newOper != channel->getUsers().end(); ++newOper)
				if (channel->isOperator(*newOper) == false)
					break ;
			if (newOper == channel->getUsers().end())
				return ;
			channel->addOperator(*newOper);
			Server::sendP2PMsg(user, *newOper, "MODE", channel->getChannelName(), newOper->getNickName() + " is operator now");
		}
		channel->deleteOperator(user);
	}
	channel->deleteUser(user);
	user.getJoinedChannels().erase(channel);
}

void Server::killUser(User &user) {
	std::cout<<user.getNickName()<<" disconnected"<<std::endl;
	_usersHistory.push_back(user);
	for (iter_channel it = user.getJoinedChannels().begin(); it != user.getJoinedChannels().end(); ++it)
		kickUserFromChannel(user, it);
	_pingData[user.getId()].isOnline = false;
	close(user.getSocketFd());
	_users.erase(Utils::findUser(_users, user.getNickName()));
}

void Server::sendSocket(int socketFd, std::string response) {
	if (send(socketFd, response.c_str(), strlen(response.c_str()), 0) < 0)
		std::cout<<"Error writing to socket"<<std::endl;
}

void whileNotTimeoutRequest(Server::PingData *pingData, bool *flag) {
	while (Utils::timer() - pingData->lastMessageTime < pingData->requestTimeout) {
		if (pingData->isOnline == false){
			*flag = true;
			std::cout<<"--------> "<<pingData->userNickName<<": "<<"AAAAAAAAAAAAAAA1"<<std::endl;
			return ;
		}
		if (pingData->restartRequest) {
			pingData->restartRequest = false;
			pingData->lastMessageTime = Utils::timer();
		}
	}
}

bool whileNotTimeoutResponse(Server::PingData *pingData, bool *flag) {
	pingData->restartResponse = false;
	pingData->responseWaiting = true;
	uint64_t timeStartWaitResp = Utils::timer();
	while ((Utils::timer() - timeStartWaitResp < pingData->responseTimeout) && pingData->restartResponse == false) {
		if (pingData->isOnline == false) {
			*flag = true;
			std::cout<<"--------> "<<pingData->userNickName<<": "<<"AAAAAAAAAAAAAAA2"<<std::endl;
			return false;
		}
	}
	std::cout<<"-------> "<<pingData->userNickName<<": "<<Utils::timer() - timeStartWaitResp<<" ? "<< pingData->responseTimeout<<std::endl;
	if (pingData->restartResponse == false) {
		*flag = true;
			std::cout<<"--------> "<<pingData->userNickName<<": "<<"AAAAAAAAAAAAAAA3"<<std::endl;
		return true;
	}
	pingData->responseWaiting = false;
	return false;
}

void* pingRequest(void *data) {
	Server::PingData *pingData = (Server::PingData *)data;
	bool flagDie = false;
	while (flagDie == false){
		whileNotTimeoutRequest(pingData, &flagDie);
		Server::sendSocket(pingData->socket, ":" + pingData->serverName + " PING :" + pingData->serverName + "\n");
		if (whileNotTimeoutResponse(pingData, &flagDie))
			pingData->disconnect = true;
	}
	return NULL;
}

void Server::createPingTread(User &user) {
	pthread_t tread;
	_pingData[user.getId()].lastMessageTime = Utils::timer();
	pthread_create(&tread, NULL, &pingRequest, &_pingData[user.getId()]);
	pthread_detach(tread);
}

void Server::clearAll() {
	_pingData.clear();
	_channels.clear();
	_usersHistory.clear();
	for (size_t i = 0; i < _users.size(); ++i)
		close(_users[i].getSocketFd());
	_users.clear();
}