#ifndef COMMANDS_HPP
#define COMMANDS_HPP

# include <vector>
# include <string>
# include <sstream>
# include "../user/user.hpp"
# include "parseRequest.hpp"
# include "service.hpp"

class Commands {
private:
	static void	admin(User &user, std::vector<std::string> &args);
	static void	away(User &user, std::vector<std::string> &args);
	static void	die(User &user, std::vector<std::string> &args);////////////////////////
	static void	error(User &user, std::vector<std::string> &args);//////////////////////
	static void	info(User &user, std::vector<std::string> &args);
	static void	invite(User &user, std::vector<std::string> &args);
	static void	ison(User &user, std::vector<std::string> &args);
	static void	join(User &user, std::vector<std::string> &args);
	static void	kick(User &user, std::vector<std::string> &args);
	static void	kill(User &user, std::vector<std::string> &args);
	static void	list(User &user, std::vector<std::string> &args);
	static void	mode(User &user, std::vector<std::string> &args);
	static void	motd(User &user, std::vector<std::string> &args);//args
	static void	names(User &user, std::vector<std::string> &args);
	static int	nick(User &user, std::vector<std::string> &args);
	static void	notice(User &user, std::vector<std::string> &args);
	static void	oper(User &user, std::vector<std::string> &args);
	static void	part(User &user, std::vector<std::string> &args);
	static void	pass(User &user, std::vector<std::string> &args);
	static int	ping(User &user, std::vector<std::string> &args);
	static int	pong(User &user, std::vector<std::string> &args);
	static void	privMsg(User &user, std::vector<std::string> &args);
	static void	quit(User &user);
	static void	rehash(User &user);
	static int	restart(User &user);
    static bool	stats(User &user, std::vector<std::string> &args);////////////////////////
	static void	time(User &user, std::vector<std::string> &args);
	static void	topic(User &user, std::vector<std::string> &args);
// static bool	checkModeParams();
// static void	setChnlMode();
// static void	setUserMode();
// static void	setChnlModeOperator();
// static void	setChnlModePrivate();
// static void	setChnlModeSecret();
// static void	setChnlModeInvite();
// static void	setChnlModeTopic();
// static void	setChnlModeOutside();
// static void	setChnlModeModerated();
// static void	setChnlModeLimit();
// static void	setChnlModeBan();
// static void	setChnlModeVoice();
// static void	setChnlModeKey();
// static void	setUserModeInvisible();
// static void	setUserModeNoticed();
// static void	setUserModeWallops();
// static void	setUserModeOperator();
	static int	user(User &user, std::vector<std::string> &args);
	static void	version(User &user, std::vector<std::string> &args);
	static void	wallops(User &user, std::vector<std::string> &args);
	static void	who(User &user, std::vector<std::string> &args);
	static void	whois(User &user, std::vector<std::string> &args);
	static void	whoWas(User &user, std::vector<std::string> &args);

	static unsigned int 			chooseCommand(User &user, std::vector<std::string> &args);
public:
	static unsigned int				process(User &user, std::string req);
};

#endif