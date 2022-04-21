#include "../Server/Server.hpp"
#include "../Hash/Hash.hpp"

void Server::passCmd(User &user, std::vector<std::string> &args) {
	if (user.isRegistered()) {
		Server::sendErrorResponse(462, user);
		return ;
	}
	if (args.size() == 1) {
		Server::sendErrorResponse(461, user, args[0]);
		return ;
	}
	user.setValidPass(args[1] == _pass);
}

void Server::nickCmd(User &user, std::vector<std::string> &args) {
	if (args.size() == 1) {
		Server::sendErrorResponse(461, user, args[0]);
		return ;
	}
	for (std::vector<User>::const_iterator it = _users.begin(); it != _users.end(); ++it) {
		if (it->getNickName() == args[1]) {
			Server::sendErrorResponse(433, user, args[1]);
			return ;
		}
	}
	user.setNickName(args[1]);
}

int Server::userCmd(User &user, std::vector<std::string> &args) {
	if (args.size() < 4) {
		Server::sendErrorResponse(461, user, args[0]);
		return 0;
	}
	if (user.getNickName() == "" || user.isValidPass() == false) {
		killUser(user);
		return 0;
	}
	user.setUserName(args[1]);
	user.setHost(args[2]);
	user.setServerName(args[3]);
	user.setRealName(args[4]);
	if (user.isRegistered() == true)
		return 0;
	user.setRegistered(true);
	Server::motdCmd(user);
	return 7;
}

void Server::quitCmd(User &user) {
	killUser(user);
}

void Server::operCmd(User &user, std::vector<std::string> &args) {
	if (args.size() != 3)
		Server::sendErrorResponse(461, user, args[0]);
	else if (_conf["operators " + args[1]] != hash::to_sha256(args[2]))
		Server::sendErrorResponse(464, user);
	else {
		user.setAdmin(true);
		Server::sendResponse(381, user);
	}
}

void Server::isonCmd(User &user, std::vector<std::string> &args) {
	std::string onlineUsers = "";
	if (args.size() < 2)
		Server::sendErrorResponse(461, user);
	else {
		for (iter_user it = _users.begin(); it != _users.end(); it++)
			for (iter_str itArg = args.begin() + 1; itArg != args.end(); itArg++)
				if (*itArg == it->getNickName())
					onlineUsers += it->getNickName() + " ";
		onlineUsers.pop_back();
		Server::sendResponse(303, user, onlineUsers);
	}
}

void Server::timeCmd(User &user, std::vector<std::string> &args) {
	if (args.size() == 1 || args[1] == _conf["name"])
		Server::sendResponse(391, user, _conf["name"], Server::getDate());
	else
		Server::sendErrorResponse(402, user, args[1]);
}

void Server::motdCmd(User &user) {
	std::ifstream infile("data/motd");
	if (infile) {
			Server::sendResponse(375, user, _conf["name"]);
		std::string line;
		while (std::getline(infile, line))
			Server::sendResponse(372, user, line);
		Server::sendResponse(376, user);
	} else
		Server::sendErrorResponse(422, user);
}

void Server::adminCmd(User &user, std::vector<std::string> &args) {
	if (args.size() == 1 || (args.size() == 2 && args[1] == _conf["name"])) {
		Server::sendResponse(256, user, " " + _conf["name"]);
		Server::sendResponse(257, user, _conf["author nickname"]);
		Server::sendResponse(258, user, _conf["author name"]);
		Server::sendResponse(259, user, _conf["mail"]);
	} else
		Server::sendErrorResponse(402, user, args[1]);
}

void Server::awayCmd(User &user, std::vector<std::string> &args) {
	if (args.size() == 1) {
		user.setAway(false);
		Server::sendResponse(305, user);
	}
	else if (args.size() > 1) {
		user.setAway(true);
		Server::sendResponse(306, user);
		user.setAutoReply(args[1]);
	}
}

void Server::infoCmd(User &user, std::vector<std::string> &args) {
	if (args.size() == 1 || (args.size() == 2 && args[1] == _conf["name"])) {
		Server::sendResponse(371, user, ">| Server Information |<");
		Server::sendResponse(371, user, "Compilation Time " + _conf["compilationTime"]);
		Server::sendResponse(371, user, "Server Version " + _conf["version"] + "." + _conf["debugLevel"]);
		Server::sendResponse(374, user);
	} else
		Server::sendErrorResponse(402, user, args[1]);
}

void Server::killCmd(User &user, std::vector<std::string> &args) {
	if (args.size() != 3)
		Server::sendErrorResponse(461, user, args[0]);
	else if (!user.isAdmin())
		Server::sendErrorResponse(481, user);
	else {
		for (iter_user it = _users.begin(); it != _users.end(); ++it) {
			if (it->getNickName() == args[1]) {
				Server::send(it->getSocketFd(), args[2] + "\n");
				Server::killUser(*it);
				return;
			}
		}
		Server::sendErrorResponse(401, user, args[1]);
	}
}

int Server::pingCmd(User &user, std::vector<std::string> &args) {
	if (args.size() < 2) {
		Server::sendErrorResponse(409, user);
		return 0;
	}
	Server::send(user.getSocketFd(), ":" + _conf["name"] + " PONG :" + args[1] + "\n");
	return 8;
}

int Server::pongCmd(User &user, std::vector<std::string> &args) {
	if (args.size() < 2) {
		Server::sendErrorResponse(409, user);
		return 0;
	}
	else if (args[1] != _conf["name"]) {
		Server::sendErrorResponse(402, user, args[1]);
		return 0;
	}
	return 8;
}

int Server::restartCmd(User &user) {
	if (!user.isAdmin()) {
		Server::sendErrorResponse(481, user);
		return 0;
	}
	return 3;
}

unsigned int Server::chooseCommand(User &user, std::vector<std::string> &args) {
	if (args[0] == "PASS") { Server::passCmd(user, args); }
	else if (args[0] == "NICK") { Server::nickCmd(user, args); }
	else if (args[0] == "USER") { return Server::userCmd(user, args); }
	else if (args[0] == "QUIT") { Server::quitCmd(user); }
	else if (!user.isRegistered()) { Server::sendErrorResponse(451, user); }
	else if (args[0] == "ADMIN") { Server::adminCmd(user, args); }
	else if (args[0] == "AWAY") { Server::awayCmd(user, args); }
	else if (args[0] == "DIE") { Server::dieCmd(user, args); }
	else if (args[0] == "ERROR") { Server::errorCmd(user, args); }
	else if (args[0] == "INFO") { Server::infoCmd(user, args); }
	else if (args[0] == "INVITE") { Server::inviteCmd(user, args); }
	else if (args[0] == "ISON") { Server::isonCmd(user, args); }
	else if (args[0] == "JOIN") { Server::joinCmd(user, args); }
	else if (args[0] == "KICK") { Server::kickCmd(user, args); }
	else if (args[0] == "KILL") { Server::killCmd(user, args); }
	else if (args[0] == "LIST") { Server::listCmd(user, args); }
	else if (args[0] == "MODE") { Server::modeCmd(user, args); }
	else if (args[0] == "MOTD") { Server::motdCmd(user); }
	else if (args[0] == "NAMES") {Server::namesCmd(user, args); }
	else if (args[0] == "NOTICE") { Server::noticeCmd(user, args); }
	else if (args[0] == "OPER") { Server::operCmd(user, args); }
	else if (args[0] == "PART") { Server::partCmd(user, args); }
	else if (args[0] == "PING") { return Server::pingCmd(user, args); }
	else if (args[0] == "PONG") { return Server::pongCmd(user, args); }
	else if (args[0] == "PRIVMSG") { Server::privMsgCmd(user, args); }
	else if (args[0] == "REHASH") { Server::rehashCmd(user); }
	else if (args[0] == "RESTART") { return Server::restartCmd(user); }
	else if (args[0] == "STATS") { return Server::statsCmd(user, args); }
	else if (args[0] == "TIME") { Server::timeCmd(user, args); }
	else if (args[0] == "TOPIC") { Server::topicCmd(user, args); }
	else if (args[0] == "VERSION") { Server::versionCmd(user, args); }
	else if (args[0] == "WALLOPS") { Server::wallopsCmd(user, args); }
	else if (args[0] == "WHO") { Server::whoCmd(user, args); }
	else if (args[0] == "WHOIS") { Server::whoisCmd(user, args); }
	else if (args[0] == "WHOWAS") { Server::whoWasCmd(user, args); }
	else Server::sendErrorResponse(421, user, args[0]);
	return 0;
}

unsigned int Server::process(User &user, std::string req) {
	if (ParseRequest::emptyRequest(req))
		return 0;
	std::vector<std::string> requestArgs = ParseRequest::parseRequest(req);
	return Server::chooseCommand(user, requestArgs);
}


void	Server::dieCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }////////////////////////
void	Server::errorCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }//////////////////////
void	Server::inviteCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
void	Server::joinCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
void	Server::kickCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
void	Server::listCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
void	Server::modeCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
void	Server::namesCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
void	Server::noticeCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
void	Server::partCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
void	Server::privMsgCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
void	Server::rehashCmd(User &user) { user.getId(); }
bool	Server::statsCmd(User &user, std::vector<std::string> &args) { user.getId(); args[1]; return false; }////////////////////////
void	Server::topicCmd(User &user, std::vector<std::string> &args) { user.getId(); args[1]; }
void	Server::versionCmd(User &user, std::vector<std::string> &args) { user.getId(); args[1]; }
void	Server::wallopsCmd(User &user, std::vector<std::string> &args) { user.getId(); args[1]; }
void	Server::whoCmd(User &user, std::vector<std::string> &args) { user.getId(); args[1]; }
void	Server::whoisCmd(User &user, std::vector<std::string> &args) { user.getId(); args[1]; }
void	Server::whoWasCmd(User &user, std::vector<std::string> &args) { user.getId(); args[1]; }
