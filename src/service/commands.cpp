#include "../Server/Server.hpp"

void Server::pass(User &user, std::vector<std::string> &args) {
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

void Server::nick(User &user, std::vector<std::string> &args) {
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

int Server::user(User &user, std::vector<std::string> &args) {
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
	Server::motd(user);
	return 7;
}

void Server::quit(User &user) {
	killUser(user);
}

void Server::timeCmd(User &user, std::vector<std::string> &args) {
//	if (args.size() == 1 || args[1] == config["server.name"])
	if (args.size() == 1)
//		Server::sendResponse(391, user, config["server.name"], Server::getDate());
		Server::sendResponse(391, user, "server_name", Server::getDate());
	else
		Server::sendErrorResponse(402, user, args[1]);
}

void Server::motd(User &user) {
	std::ifstream infile("data/motd");
	if (infile) {
		//	Server::sendResponse(375, user, config["server.name"]);
		Server::sendResponse(375, user, "server_name");
		std::string line;
		while (std::getline(infile, line))
			Server::sendResponse(372, user, line);
		Server::sendResponse(376, user);
	} else
		Server::sendErrorResponse(422, user);
}

unsigned int Server::chooseCommand(User &user, std::vector<std::string> &args) {
	if (args[0] == "PASS") { Commands:pass(user, args); }
	else if (args[0] == "NICK") { Server::nick(user, args); }
	else if (args[0] == "USER") { return Server::user(user, args); }
	else if (args[0] == "QUIT") { Server::quit(user); }
	else if (!user.isRegistered()) { Server::sendErrorResponse(451, user); }
	else if (args[0] == "ADMIN") { Server::admin(user, args); }
	else if (args[0] == "AWAY") { Server::away(user, args); }
	else if (args[0] == "DIE") { Server::die(user, args); }
	else if (args[0] == "ERROR") { Server::error(user, args); }
	else if (args[0] == "INFO") { Server::info(user, args); }
	else if (args[0] == "INVITE") { Server::invite(user, args); }
	else if (args[0] == "ISON") { Server::ison(user, args); }
	else if (args[0] == "JOIN") { Server::join(user, args); }
	else if (args[0] == "KICK") { Server::kick(user, args); }
	else if (args[0] == "KILL") { Server::kill(user, args); }
	else if (args[0] == "LIST") { Server::list(user, args); }
	else if (args[0] == "MODE") { Server::mode(user, args); }
	else if (args[0] == "MOTD") { Server::motd(user); }
	else if (args[0] == "NAMES") {Server::names(user, args); }
	else if (args[0] == "NOTICE") { Server::notice(user, args); }
	else if (args[0] == "OPER") { Server::oper(user, args); }
	else if (args[0] == "PART") { Server::part(user, args); }
	else if (args[0] == "PING") { return Server::ping(user, args); }
	else if (args[0] == "PONG") { return Server::pong(user, args); }
	else if (args[0] == "PRIVMSG") { Server::privMsg(user, args); }
	else if (args[0] == "REHASH") { Server::rehash(user); }
	else if (args[0] == "RESTART") { return Server::restart(user); }
	else if (args[0] == "STATS") { return Server::stats(user, args); }
	else if (args[0] == "TIME") { Server::time(user, args); }
	else if (args[0] == "TOPIC") { Server::topic(user, args); }
	else if (args[0] == "VERSION") { Server::version(user, args); }
	else if (args[0] == "WALLOPS") { Server::wallops(user, args); }
	else if (args[0] == "WHO") { Server::who(user, args); }
	else if (args[0] == "WHOIS") { Server::whois(user, args); }
	else if (args[0] == "WHOWAS") { Server::whoWas(user, args); }
	else Server::sendErrorResponse(421, user, args[0]);
	return 0;
}

unsigned int Server::process(User &user, std::string req) {
	if (ParseRequest::emptyRequest(req))
		return 0;
	std::vector<std::string> requestArgs = ParseRequest::parseRequest(req);
	return Server::chooseCommand(user, requestArgs);
}