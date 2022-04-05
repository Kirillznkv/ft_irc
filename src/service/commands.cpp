#include "commands.hpp"

unsigned int Commands::chooseCommand(User &user, std::vector<std::string> &args) {

	if (args[0] == "PASS") { Commands:pass(user, args); }
	else if (args[0] == "NICK") { return Commands::nick(user, args); }
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
	else if (args[0] == "MOTD") { Commands::motd(user, args); }
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