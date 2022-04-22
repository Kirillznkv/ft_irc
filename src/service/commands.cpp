#include "../Server/Server.hpp"
#include "../Hash/Hash.hpp"

unsigned int Server::process(User &user, std::string req) {
	if (ParseRequest::emptyRequest(req))
		return 0;
	std::vector<std::string> requestArgs = ParseRequest::parseRequest(req);
	return Server::chooseCommand(user, requestArgs);
}

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
		Server::sendResponse(391, user, _conf["name"], Utils::getDate());
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

void Server::rehashCmd(User &user) {
	if (!user.isAdmin())
		Server::sendErrorResponse(481, user);
	else {
		_conf.reload();
		Server::sendResponse(382, user);
	}
}

void Server::versionCmd(User &user, std::vector<std::string> &args) {
	if (args.size() < 2)
		Server::sendErrorResponse(409, user);
	else if (args[1] != _conf["name"])
		Server::sendErrorResponse(402, user, args[1]);
	else
		Server::sendResponse(351, user, _conf["version"], _conf["debugLevel"], _conf["name"], _conf["release"]);
}

void Server::wallopsCmd(User &user, std::vector<std::string> &args) {
	if (args.size() < 2)
		Server::sendErrorResponse(461, user, args[0]);
	else {
		for (iter_user it = _users.begin(); it != _users.end(); ++it)
			if (it->isAdmin())
				Server::sendP2PMsg(user, *it, args[0], args[1]);
	}
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


void Server::joinToChannel(User &user, std::string chName, std::string chPass) {
	iter_channel it = Utils::findChannel(_channels, chName);
	if (Utils::isUserExist(it->getUsers(), user.getNickName())) {
		Server::sendErrorResponse(443, user, chName);
		return ;
	}
	if (Utils::isUserExist(it->getBanList(), user.getNickName())) {
		Server::sendErrorResponse(474, user, chName);
		return ;
	}
	if (it->isInviteOnly() && Utils::isUserExist(it->getInvites(), user.getNickName()) == false) {
		Server::sendErrorResponse(473, user, chName);
		return ;
	}
	bool isAdded = it->addUser(user, chPass);
	if (isAdded == false)
		Server::sendErrorResponse(475, user, chName);
	else {
		user.getJoinedChannels().push_back(*it);
		for (iter_user userInChannel = it->getUsers().begin(); userInChannel != it->getUsers().end(); ++userInChannel)
			Server::sendP2PMsg(user, *userInChannel, "JOIN", chName);
		if (it->getChannelTopic() != "")
			Server::sendResponse(332, user, chName, it->getChannelTopic());
		else
			Server::sendResponse(331, user, chName);
		Server::sendResponse(353, user, "= " + chName, Utils::getUsers(*it));
		Server::sendResponse(366, user, chName);
	}
}
void Server::createAndJoinToChannel(User &user, std::string chName, std::string chPass) {
	Channel newChannel = Channel(chName, user, chPass);
	_channels.push_back(newChannel);
	Server::sendP2PMsg(user, user, "JOIN", chName);
	Server::sendResponse(331, user, chName, newChannel.getChannelTopic());
	Server::sendResponse(353, user, "= " + chName, "@" + user.getNickName());
	Server::sendResponse(366, user, chName);
}

void Server::joinCmd(User &user, std::vector<std::string> &args) {
	if (args.size() == 1) {
		Server::sendErrorResponse(461, user, args[0]);
		return ;
	}
	std::vector<std::string> channels, passwords;
	channels = Utils::split(args[1], ',');
	passwords.reserve(channels.size());
	if (args.size() == 3)
		passwords = Utils::split(args[2], ',');
	for (size_t i = 0; i < channels.size(); ++i){
		std::string chName = channels[i], chPass = passwords[i];
		if (Utils::isValidChannelName(chName) == false)
			Server::sendErrorResponse(403, user, chName);
		else if (Utils::isChannelExist(_channels, chName))
			joinToChannel(user, chName, chPass);
		else
			createAndJoinToChannel(user, chName, chPass);
	}
}

void Server::inviteCmd(User &user, std::vector<std::string> &args) {
	if (args.size() < 3) {
		Server::sendErrorResponse(461, user, args[0]);
		return ;
	}
	std::string invUser = args[1], invChannel = args[2];
	if (Utils::isChannelExist(_channels, invChannel) == false) {
		Server::sendErrorResponse(403, user, invChannel);
		return ;
	}
	if (Utils::isUserExist(_users, invUser) == false) {
		Server::sendErrorResponse(401, user, invUser);
		return ;
	}
	iter_user itInvUser = Utils::findUser(_users, invUser);
	iter_channel itInvChannel = Utils::findChannel(_channels, invChannel);
	if (Utils::isUserExist(itInvChannel->getUsers(), user.getNickName()) == false) {
		Server::sendErrorResponse(442, user, invChannel);
		return ;
	}
	if (Utils::isUserExist(itInvChannel->getUsers(), invUser) == false) {
		Server::sendErrorResponse(443, user, invUser, invChannel);
		return ;
	}
	if (itInvChannel->isInviteOnly() && Utils::isUserExist(itInvChannel->getOpers(), user.getNickName()) == false) {
		Server::sendErrorResponse(482, user, invChannel);
		return ;
	}
	itInvChannel->addUserToInviteList(*itInvUser);
	Server::sendResponse(341, user, invChannel, invUser);
	Server::sendP2PMsg(user, *itInvUser, args[0], itInvUser->getNickName(), invChannel);
	if (itInvUser->isAway())
		Server::sendResponse(301, user, invUser, itInvUser->getAutoReply());
}

void Server::topicCmd(User &user, std::vector<std::string> &args) {
	if (args.size() < 2) {
		Server::sendErrorResponse(461, user, args[0]);
		return ;
	}
	std::string chName = args[1];
	if (Utils::isChannelExist(_channels, chName) == false) {
		Server::sendErrorResponse(403, user, chName);
		return ;
	}
	iter_channel itChannel = Utils::findChannel(_channels, chName);
	if (Utils::isUserExist(itChannel->getUsers(), user.getNickName()) == false) {
		Server::sendErrorResponse(442, user, args[1]);
		return ;
	}
	if (args.size() == 2) {
		if (itChannel->getChannelTopic() != "")
			Server::sendResponse(332, user, chName, itChannel->getChannelTopic());
		else
			Server::sendResponse(331, user, chName);
	}
	else {
		if (itChannel->isTopicByOper() && Utils::isUserExist(itChannel->getOpers(), user.getNickName()) == false)
			Server::sendErrorResponse(482, user, chName);
		else {
			itChannel->setTopic(args[2]);
			for (iter_user usr = itChannel->getUsers().begin(); usr != itChannel->getUsers().end(); ++usr)
				Server::sendP2PMsg(user, *usr, args[0], chName, args[2]);
		}
	}
}

void	Server::dieCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }////////////////////////
void	Server::errorCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }//////////////////////
void	Server::kickCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
void	Server::listCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
void	Server::modeCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
void	Server::namesCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
void	Server::noticeCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
void	Server::partCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
void	Server::privMsgCmd(User &user, std::vector<std::string> &args) { user.getId(); args[0]; }
bool	Server::statsCmd(User &user, std::vector<std::string> &args) { user.getId(); args[1]; return false; }////////////////////////
void	Server::whoCmd(User &user, std::vector<std::string> &args) { user.getId(); args[1]; }
void	Server::whoisCmd(User &user, std::vector<std::string> &args) { user.getId(); args[1]; }
void	Server::whoWasCmd(User &user, std::vector<std::string> &args) { user.getId(); args[1]; }
