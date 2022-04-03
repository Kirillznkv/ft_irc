#ifndef COMMANDS_HPP
#define COMMANDS_HPP

class Commands {
public:
	static void	admin();
	static void	away();
	static void	die();////////////////////////
	static void	error();//////////////////////
	static void	info();
	static void	invite();
	static void	ison();
	static void	join();
	static void	kick();
	static void	kill();
	static void	list();
	static void	mode();
	static void	motd();
	static void	names();
	static int	nick();
	static void	notice();
	static void	oper();
	static void	part();
	static void	pass();
	static int	ping();
	static int	pong();
	static void	privMsg();
	static void	quit();
	static void	rehash();
	static int	restart();
    static bool	stats();////////////////////////
	static void	time();
	static void	topic();
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
	static int	user();
	static int	users();///////////////////////////
	static void	version();
	static void	wallops();
	static void	who();
	static void	whois();
	static void	whoWas();
};

#endif