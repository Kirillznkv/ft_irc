#ifndef SERVER_HPP
#define SERVER_HPP

# include <iostream>
# include <vector>
# include <string>
# include <sstream>
# include <fstream>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/time.h>
# include "../User/User.hpp"
# include "../Config/Config.hpp"
# include "../Service/ParseRequest.hpp"

class Server
{
private:
    int                         _fd;
    unsigned short int          _port;
    unsigned long               _ipAddr;
	std::string					_pass;
	std::vector<User>			_users;

public:
    Server();
    ~Server();
    void	createConnection();
private:
	void	killUser(User &user) const;
	////////////////////////////////
	//----------Commands----------//
	////////////////////////////////
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
	void	motd(User &user);// Done
	void	names(User &user, std::vector<std::string> &args);
	void	nick(User &user, std::vector<std::string> &args);// Done
	void	notice(User &user, std::vector<std::string> &args);
	void	oper(User &user, std::vector<std::string> &args);
	void	part(User &user, std::vector<std::string> &args);
	void	pass(User &user, std::vector<std::string> &args);// Done
	int		ping(User &user, std::vector<std::string> &args);
	int		pong(User &user, std::vector<std::string> &args);
	void	privMsg(User &user, std::vector<std::string> &args);
	void	quit(User &user);// Done
	void	rehash(User &user);
	int		restart(User &user);
	bool	stats(User &user, std::vector<std::string> &args);////////////////////////
	void	timeCmd(User &user, std::vector<std::string> &args);// Done
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
	int		user(User &user, std::vector<std::string> &args);// Done
	void	version(User &user, std::vector<std::string> &args);
	void	wallops(User &user, std::vector<std::string> &args);
	void	who(User &user, std::vector<std::string> &args);
	void	whois(User &user, std::vector<std::string> &args);
	void	whoWas(User &user, std::vector<std::string> &args);
	unsigned int 	chooseCommand(User &user, std::vector<std::string> &args);
	unsigned int	process(User &user, std::string req);
	////////////////////////////////
	//----------Service-----------//
	////////////////////////////////
	uint64_t					timer();
	std::string					getDate();
	std::vector<std::string>	split(const std::string& str, char delimeter);
	void						sendErrorResponse(unsigned int code, const User &user, std::string arg1="", std::string arg2="");
	void						sendResponse(unsigned int code, const User &user, std::string arg1="", std::string arg2="", \
																std::string arg3="", std::string arg4="", std::string arg5="", \
																std::string arg6="", std::string arg7="");
};

#endif