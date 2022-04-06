#include "Commands.hpp"

Commands::Commands(const Server &server) : _server(server) {}
Commands::~Commands() {}

void Commands::pass(User &user, std::vector<std::string> &args) {
	if (user.isRegistered()) {
		Service::sendErrorResponse(462, user);
		return ;
	}
	if (args.size() == 1) {
		Service::sendErrorResponse(461, user, args[0]);
		return ;
	}
	user.setValidPass(_server.isTruePass(args[1]));
}

void Commands::nick(User &user, std::vector<std::string> &args) {
	if (args.size() == 1) {
		Service::sendErrorResponse(461, user, args[0]);
		return ;
	}
	for (std::vector<User>::const_iterator it = _server._users.begin(); it != _server._users.end(); ++it) {
		if (it->getNickName() == args[1]) {
			Service::sendErrorResponse(433, user, args[1]);
			return ;
		}
	}
	user.setNickName(args[1]);
}

int Commands::user(User &user, std::vector<std::string> &args) {
	if (args.size() < 4) {
		Service::sendErrorResponse(461, user, args[0]);
		return 0;
	}
	if (user.getNickName() == "" || user.isValidPass() == false) {
		_server.killUser(user);
		return 0;
	}
	user.setUserName(args[1]);
	user.setHost(args[2]);
	user.setServerName(args[3]);
	user.setRealName(args[4]);
	if (user.isRegistered() == true)
		return 0;
	user.setRegistered(true);
	Commands::motd(user);
	return NEW_REGISTRATION_CODE;
}

void Commands::quit(User &user) {
	_server.killUser(user);
}

void Commands::time(User &user, std::vector<std::string> &args) {
//	if (args.size() == 1 || args[1] == config["server.name"])
	if (args.size() == 1)
//		Service::sendResponse(391, user, config["server.name"], Service::getDate());
		Service::sendResponse(391, user, "server_name", Service::getDate());
	else
		Service::sendErrorResponse(402, user, args[1]);
}

void Commands::motd(User &user) {
	std::ifstream infile("src/motd");
	if (infile) {
		//	Service::sendResponse(375, user, config["server.name"]);
		Service::sendResponse(375, user, "server_name");
		std::string line;
		while (std::getline(infile, line))
			Service::sendResponse(372, user, line);
		Service::sendResponse(376, user);
	} else
		Service::sendErrorResponse(422, user);
}

unsigned int Commands::chooseCommand(User &user, std::vector<std::string> &args) {
	if (args[0] == "PASS") { Commands:pass(user, args); }
	else if (args[0] == "NICK") { Commands::nick(user, args); }
	else if (args[0] == "USER") { return Commands::user(user, args); }
	else if (args[0] == "QUIT") { Commands::quit(user); }
	else if (!user.isRegistered()) { Service::sendErrorResponse(451, user); }
	else if (args[0] == "ADMIN") { Commands::admin(user, args); }
	else if (args[0] == "AWAY") { Commands::away(user, args); }
	else if (args[0] == "DIE") { Commands::die(user, args); }
	else if (args[0] == "ERROR") { Commands::error(user, args); }
	else if (args[0] == "INFO") { Commands::info(user, args); }
	else if (args[0] == "INVITE") { Commands::invite(user, args); }
	else if (args[0] == "ISON") { Commands::ison(user, args); }
	else if (args[0] == "JOIN") { Commands::join(user, args); }
	else if (args[0] == "KICK") { Commands::kick(user, args); }
	else if (args[0] == "KILL") { Commands::kill(user, args); }
	else if (args[0] == "LIST") { Commands::list(user, args); }
	else if (args[0] == "MODE") { Commands::mode(user, args); }
	else if (args[0] == "MOTD") { Commands::motd(user); }
	else if (args[0] == "NAMES") {Commands::names(user, args); }
	else if (args[0] == "NOTICE") { Commands::notice(user, args); }
	else if (args[0] == "OPER") { Commands::oper(user, args); }
	else if (args[0] == "PART") { Commands::part(user, args); }
	else if (args[0] == "PING") { return Commands::ping(user, args); }
	else if (args[0] == "PONG") { return Commands::pong(user, args); }
	else if (args[0] == "PRIVMSG") { Commands::privMsg(user, args); }
	else if (args[0] == "REHASH") { Commands::rehash(user); }
	else if (args[0] == "RESTART") { return Commands::restart(user); }
	else if (args[0] == "STATS") { return Commands::stats(user, args); }
	else if (args[0] == "TIME") { Commands::time(user, args); }
	else if (args[0] == "TOPIC") { Commands::topic(user, args); }
	else if (args[0] == "VERSION") { Commands::version(user, args); }
	else if (args[0] == "WALLOPS") { Commands::wallops(user, args); }
	else if (args[0] == "WHO") { Commands::who(user, args); }
	else if (args[0] == "WHOIS") { Commands::whois(user, args); }
	else if (args[0] == "WHOWAS") { Commands::whoWas(user, args); }
	else Service::sendErrorResponse(421, user, args[0]);
	return 0;
}

unsigned int Commands::process(User &user, std::string req) {
	if (ParseRequest::emptyRequest(req))
		return 0;
	std::vector<std::string> requestArgs = ParseRequest::parseRequest(req);
	return Commands::chooseCommand(user, requestArgs);
}