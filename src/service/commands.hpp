#ifndef COMMANDS_HPP
#define COMMANDS_HPP

# include <vector>
# include <string>
# include <sstream>
# include "../Server/Server.hpp"
# include "../User/User.hpp"
# include "ParseRequest.hpp"
# include "Service.hpp"

class Commands {
private:
	const Server	&_server;
	Commands(const Commands &);
	Commands &operator=(const Commands &);
private:
	void	admin(User &user, std::vector<std::string> &args);
	void	away(User &user, std::vector<std::string> &args);
	void	die(User &user, std::vector<std::string> &args);////////////////////////
	void	error(User &user, std::vector<std::string> &args);//////////////////////
	void	info(User &user, std::vector<std::string> &args);
	void	invite(User &user, std::vector<std::string> &args);
	void	ison(User &user, std::vector<std::string> &args);
	void	join(User &user, std::vector<std::string> &args);
	void	kick(User &user, std::vector<std::string> &args);
	void	kill(User &user, std::vector<std::string> &args);
	void	list(User &user, std::vector<std::string> &args);
	void	mode(User &user, std::vector<std::string> &args);
	void	motd(User &user);
	void	names(User &user, std::vector<std::string> &args);
	void	nick(User &user, std::vector<std::string> &args);
	void	notice(User &user, std::vector<std::string> &args);
	void	oper(User &user, std::vector<std::string> &args);
	void	part(User &user, std::vector<std::string> &args);
	void	pass(User &user, std::vector<std::string> &args);
	int		ping(User &user, std::vector<std::string> &args);
	int		pong(User &user, std::vector<std::string> &args);
	void	privMsg(User &user, std::vector<std::string> &args);
	void	quit(User &user);
	void	rehash(User &user);
	int		restart(User &user);
	bool	stats(User &user, std::vector<std::string> &args);////////////////////////
	void	time(User &user, std::vector<std::string> &args);
	void	topic(User &user, std::vector<std::string> &args);
// bool	checkModeParams();
// void	setChnlMode();
// void	setUserMode();
// void	setChnlModeOperator();
// void	setChnlModePrivate();
// void	setChnlModeSecret();
// void	setChnlModeInvite();
// void	setChnlModeTopic();
// void	setChnlModeOutside();
// void	setChnlModeModerated();
// void	setChnlModeLimit();
// void	setChnlModeBan();
// void	setChnlModeVoice();
// void	setChnlModeKey();
// void	setUserModeInvisible();
// void	setUserModeNoticed();
// void	setUserModeWallops();
// void	setUserModeOperator();
	int		user(User &user, std::vector<std::string> &args);
	void	version(User &user, std::vector<std::string> &args);
	void	wallops(User &user, std::vector<std::string> &args);
	void	who(User &user, std::vector<std::string> &args);
	void	whois(User &user, std::vector<std::string> &args);
	void	whoWas(User &user, std::vector<std::string> &args);

	unsigned int 	chooseCommand(User &user, std::vector<std::string> &args);
public:
	Commands(const Server &server);
	~Commands();
	unsigned int	process(User &user, std::string req);
};

#endif