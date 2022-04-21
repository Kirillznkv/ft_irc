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
# include "../Channel/Channel.hpp"

class Channel;

class Server
{
private:
	typedef std::vector<User>::iterator			iter_user;
	typedef std::vector<Channel>::iterator		iter_channel;
	typedef std::vector<std::string>::iterator	iter_str;
    int                         _fd;
    unsigned short int          _port;
    unsigned long               _ipAddr;
	std::string					_pass;
	std::vector<User>			_users;
	std::vector<Channel>		_channels;
	Config						_conf;
public:
    Server(unsigned short int port, std::string pass);
    ~Server();
    void		createConnection();
	void		start();
	static void	send(int socketFd, std::string response);
private:
	void		killUser(User &user);
	////////////////////////////////
	//----------Commands----------//
	////////////////////////////////
	void	adminCmd(User &user, std::vector<std::string> &args);// Done
	void	awayCmd(User &user, std::vector<std::string> &args);// Done
	void	dieCmd(User &user, std::vector<std::string> &args);////////////////////////
	void	errorCmd(User &user, std::vector<std::string> &args);//////////////////////
	void	infoCmd(User &user, std::vector<std::string> &args);// Done
	void	inviteCmd(User &user, std::vector<std::string> &args);
	void	isonCmd(User &user, std::vector<std::string> &args);// Done
	void	joinCmd(User &user, std::vector<std::string> &args);
	void	kickCmd(User &user, std::vector<std::string> &args);
	void	killCmd(User &user, std::vector<std::string> &args);// Done
	void	listCmd(User &user, std::vector<std::string> &args);
	void	modeCmd(User &user, std::vector<std::string> &args);
	void	motdCmd(User &user);// Done
	void	namesCmd(User &user, std::vector<std::string> &args);
	void	nickCmd(User &user, std::vector<std::string> &args);// Done
	void	noticeCmd(User &user, std::vector<std::string> &args);
	void	operCmd(User &user, std::vector<std::string> &args);// Done
	void	partCmd(User &user, std::vector<std::string> &args);
	void	passCmd(User &user, std::vector<std::string> &args);// Done
	int		pingCmd(User &user, std::vector<std::string> &args);
	int		pongCmd(User &user, std::vector<std::string> &args);
	void	privMsgCmd(User &user, std::vector<std::string> &args);
	void	quitCmd(User &user);// Done
	void	rehashCmd(User &user);
	int		restartCmd(User &user);
	bool	statsCmd(User &user, std::vector<std::string> &args);////////////////////////
	void	timeCmd(User &user, std::vector<std::string> &args);// Done
	void	topicCmd(User &user, std::vector<std::string> &args);
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
	int		userCmd(User &user, std::vector<std::string> &args);// Done
	void	versionCmd(User &user, std::vector<std::string> &args);
	void	wallopsCmd(User &user, std::vector<std::string> &args);
	void	whoCmd(User &user, std::vector<std::string> &args);
	void	whoisCmd(User &user, std::vector<std::string> &args);
	void	whoWasCmd(User &user, std::vector<std::string> &args);
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
