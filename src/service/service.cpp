#include "../Server/Server.hpp"

void Server::sendErrorResponse(unsigned int code, const User &user, std::string arg1, std::string arg2) {
	std::string res = ":" + _conf["name"] + " " + std::to_string(code) + " " + user.getNickName();
	switch (code) {
		case 401: res += " " + arg1 + " :No such nick/channel\n"; break;
		case 402: res += " " + arg1 + " :No such server\n"; break;
		case 403: res += " " + arg1 + " :No such channel\n"; break;
		case 404: res += " " + arg1 + " :Cannot send to channel\n"; break;
		case 405: res += " " + arg1 + " :You have joined too many channels\n"; break;
		case 406: res += " " + arg1 + " :There was no such nickname\n"; break;
		case 407: res += " " + arg1 + " :Duplicate recipients. No arg1 delivered\n"; break;
		case 409: res += " :No origin specified\n"; break;
		case 411: res += " :No recipient given (" + arg1 + ")\n"; break;
		case 412: res += " :No text to send\n"; break;
		case 413: res += " " + arg1 + " :No toplevel domain specified\n"; break;
		case 414: res += " " + arg1 + " :Wildcard in toplevel domain\n"; break;
		case 421: res += " " + arg1 + " :Unknown command\n"; break;
		case 422: res += " :MOTD File is missing\n"; break;
		case 423: res += " " + arg1 + " :No administrative info available\n"; break;
		case 424: res += " :File error doing \n" + arg1 + " on " + arg2 + "\n"; break;
		case 431: res += " :No nickname given\n"; break;
		case 432: res += " " + arg1 + " :Erroneus nickname\n"; break;
		case 433: res += " " + arg1 + " :Nickname is already in use\n"; break;
		case 436: res += " " + arg1 + " :Nickname collision KILL\n"; break;
		case 441: res += " " + arg1 + " " + arg2 + " :They aren't on that channel\n"; break;
		case 442: res += " " + arg1 + " :You're not on that channel\n"; break;
		case 443: res += " " + arg1 + " " + arg2 + " :is already on channel\n"; break;
		case 444: res += " " + arg1 + " :User not logged in\n"; break;
		case 445: res += " :SUMMON has been disabled\n"; break;
		case 446: res += " :USERS has been disabled\n"; break;
		case 451: res += " :You have not registered\n"; break;
		case 461: res += " " + arg1 + " :Not enough parameters\n"; break;
		case 462: res += " :You may not reregister\n"; break;
		case 463: res += " :Your host isn't among the privileged\n"; break;
		case 464: res += " :Password incorrect\n"; break;
		case 465: res += " :You are banned from this server\n"; break;
		case 467: res += " " + arg1 + " :Channel key already set\n"; break;
		case 471: res += " " + arg1 + " :Cannot join channel (+l)\n"; break;
		case 472: res += " " + arg1 + " :is unknown mode char to me\n"; break;
		case 473: res += " " + arg1 + " :Cannot join channel (+i)\n"; break;
		case 474: res += " " + arg1 + " :Cannot join channel (+b)\n"; break;
		case 475: res += " " + arg1 + " :Cannot join channel (+k)\n"; break;
		case 481: res += " :Permission Denied- You're not an IRC operator\n"; break;
		case 482: res += " " + arg1 + " :You're not channel operator\n"; break;
		case 483: res += " :You cant kill a server!\n"; break;
		case 491: res += " :No O-lines for your host\n"; break;
		case 501: res += " :Unknown MODE flag\n"; break;
		case 502: res += " :Cant change mode for other users\n"; break;
		default: res += "UNKNOWN ERROR\n"; break;
	}
	Server::sendSocket(user.getSocketFd(), res);
}

void Server::sendResponse(unsigned int code, const User &user, std::string arg1, std::string arg2, std::string arg3, \
									std::string arg4, std::string arg5, std::string arg6, std::string arg7) {
	std::string res = ":" + _conf["name"] + " " + std::to_string(code) + " " + user.getNickName() + " ";
	switch (code) {
		case 302: res += ":" + arg1 + "\n"; break;
		case 303: res += ":" + arg1 + "\n"; break;
		case 301: res += arg1 + " :" + arg2 + "\n"; break;
		case 305: res += ":You are no longer marked as being away\n"; break;
		case 306: res += ":You have been marked as being away\n"; break;
		case 311: res += arg1 + " " + arg2 + " " + arg3 + " * :" + arg4 + "\n"; break;
		case 312: res += arg1 + " " + arg2 + " :" + arg3 + "\n"; break;
		case 313: res += arg1 + " :is an IRC operator\n"; break;
		case 317: res += arg1 + " " + arg2 + " " + arg3 + " :seconds idle\n"; break;
		case 318: res += arg1 + " :End of /WHOIS list\n"; break;
		case 319: res += arg1 + " :" + arg2 + "\n"; break;
		case 314: res += arg1 + " " + arg2 + " " + arg3 + " * :" + arg4 + "\n"; break;
		case 369: res += arg1 + " :End of WHOWAS\n"; break;
		case 321: res += "Channel :Users  Name\n"; break;
		case 322: res += arg1 + " " + arg2 + " :" + arg3 + "\n"; break;
		case 323: res += ":End of /LIST\n"; break;
		case 324: res += arg1 + " +" + arg2 + "\n"; break;
		case 331: res += arg1 + " :No topic is set\n"; break;
		case 332: res += arg1 + " :" + arg2 + "\n"; break;
		case 341: res += arg1 + " " + arg2 + "\n"; break;
		case 342: res += arg1 + " :Summoning user to IRC\n"; break;
		case 351: res += arg1 + "." + arg2 + " " + arg3 + " :" + arg4 + "\n"; break;
		case 352: res += arg1 + " " + arg2 + " " + arg3 + " " + arg4 + " ";
				  res += arg5 + " H :" + arg6 + " " + arg7 + "\n"; break;
		case 315: res += arg1 + " :End of /WHO list\n"; break;
		case 353: res += arg1 + " :" + arg2 + "\n"; break;
		case 366: res += arg1 + " :End of /NAMES list\n"; break;
		case 364: res += arg1 + " " + arg2 + ": " + arg3 + " " + arg4 + "\n"; break;
		case 365: res += arg1 + " :End of /LINKS list\n"; break;
		case 367: res += arg1 + " " + arg2 + "\n"; break;
		case 368: res += arg1 + " :End of channel ban list\n"; break;
		case 371: res += ":" + arg1 + "\n"; break;
		case 374: res += ":End of /INFO list\n"; break;
		case 375: res += ":- " + arg1 + " Message of the day - \n"; break;
		case 372: res += ":- " + arg1 + "\n"; break;
		case 376: res += ":End of /MOTD command\n"; break;
		case 381: res += ":You are now an IRC operator\n"; break;
		case 382: res += arg1 + " :Rehashing\n"; break;
		case 391: res += arg1 + " :" + arg2 + "\n"; break;
		case 392: res += ":UserID   Terminal  Host\n"; break;
		case 393: res += ":%-8s %-9s %-8s\n"; break;
		case 394: res += ":End of users\n"; break;
		case 395: res += ":Nobody logged in\n"; break;
		case 200: res += "Link " + arg1 + " " + arg2 + " " + arg3 + "\n"; break;
		case 201: res += "Try. " + arg1 + " " + arg2 + "\n"; break;
		case 202: res += "H.S. " + arg1 + " " + arg2 + "\n"; break;
		case 203: res += "???? " + arg1 + " " + arg2 + "\n"; break;
		case 204: res += "Oper " + arg1 + " " + arg2 + "\n"; break;
		case 205: res += "User " + arg1 + " " + arg2 + "\n"; break;
		case 206: res += "Serv " + arg1 + " " + arg2 + "S " + arg3 + "C ";
				  res += arg4 + " " + arg5 + "@H\n"; break;
		case 208: res += arg1 + " 0 " + arg2 + "\n"; break;
		case 261: res += "File " + arg1 + " " + arg2 + "\n"; break;
		case 211: res += arg1 + " " + arg2 + " " + arg3 + " " + arg4 + " ";
				  res += arg5 + " H " + arg6 + "\n"; break;
		case 212: res += arg1 + " " + arg2 + "\n"; break;
		case 213: res += "C " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n"; break;
		case 214: res += "N " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n"; break;
		case 215: res += "I " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n"; break;
		case 216: res += "K " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n"; break;
		case 218: res += "Y " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n"; break;
		case 219: res += arg1 + " :End of /STATS report\n"; break;
		case 241: res += "L " + arg1 + " * " + arg2 + " " + arg3 + "\n"; break;
		case 242: res += ":Server Up %d days %d:%02d:%02d\n"; break;
		case 243: res += "O " + arg1 + " * " + arg2 + "\n"; break;
		case 244: res += "H " + arg1 + " * " + arg2 + "\n"; break;
		case 221: res += arg1 + "\n"; break;
		case 251: res += ":There are " + arg1 + " users and " + arg2;
				  res += " invisible on " + arg3 + " servers\n"; break;
		case 252: res += arg1 + " :operator(s) online\n"; break;
		case 253: res += arg1 + " :unknown connection(s)\n"; break;
		case 254: res += arg1 + " :channels formed\n"; break;
		case 255: res += ":I have " + arg1 + " clients and " + arg2 + " servers\n"; break;
		case 256: res += arg1 + " :Administrative info\n"; break;
		case 257: res += ":Name     " + arg1 + "\n"; break;
		case 258: res += ":Nickname " + arg1 + "\n"; break;
		case 259: res += ":E-Mail   " + arg1 + "\n"; break;
		default: res += "UNKNOWN REPLY\n"; break;
	}
	Server::sendSocket(user.getSocketFd(), res);
}

void Server::sendP2PMsg(User &sender, User& recipient, std::string arg1, std::string arg2, std::string arg3) {
	std::string msg = ":" + sender.getNickName() + "!" + sender.getUserName() + "@" + sender.getRealHost() + " ";
	if (arg1 != "" && arg2 == "")
		msg += arg1 + "\n";
	else if (arg1 != "" && arg3 == "")
		msg += arg1 + " :" + arg2 + "\n";
	else if (arg1 != "")
		msg += arg1 + " " + arg2 + " :" + arg3 + "\n";
	Server::sendSocket(recipient.getSocketFd(), msg);
}
