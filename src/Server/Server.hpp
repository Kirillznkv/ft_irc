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
class User;

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
	void	inviteCmd(User &user, std::vector<std::string> &args);// Done
	void	isonCmd(User &user, std::vector<std::string> &args);// Done
	void	joinCmd(User &user, std::vector<std::string> &args);// Done
	void	kickCmd(User &user, std::vector<std::string> &args);// Done
	void	killCmd(User &user, std::vector<std::string> &args);// Done
	void	listCmd(User &user, std::vector<std::string> &args);// Done
	void	modeCmd(User &user, std::vector<std::string> &args);
	void	motdCmd(User &user);// Done
	void	namesCmd(User &user, std::vector<std::string> &args);// Done
	void	nickCmd(User &user, std::vector<std::string> &args);// Done
	void	noticeCmd(User &user, std::vector<std::string> &args);
	void	operCmd(User &user, std::vector<std::string> &args);// Done
	void	partCmd(User &user, std::vector<std::string> &args);// Done
	void	passCmd(User &user, std::vector<std::string> &args);// Done
	int		pingCmd(User &user, std::vector<std::string> &args);// Done
	int		pongCmd(User &user, std::vector<std::string> &args);// Done
	void	privMsgCmd(User &user, std::vector<std::string> &args);
	void	quitCmd(User &user);// Done
	void	rehashCmd(User &user);// Done
	int		restartCmd(User &user);// Done
	bool	statsCmd(User &user, std::vector<std::string> &args);////////////////////////
	void	timeCmd(User &user, std::vector<std::string> &args);// Done
	void	topicCmd(User &user, std::vector<std::string> &args);// Done
	int		userCmd(User &user, std::vector<std::string> &args);// Done
	void	versionCmd(User &user, std::vector<std::string> &args);// Done
	void	wallopsCmd(User &user, std::vector<std::string> &args);// Done
	void	whoCmd(User &user, std::vector<std::string> &args);
	void	whoisCmd(User &user, std::vector<std::string> &args);
	void	whoWasCmd(User &user, std::vector<std::string> &args);
	unsigned int 	chooseCommand(User &user, std::vector<std::string> &args);
	unsigned int	process(User &user, std::string req);
	////////////////////////////////
	//----------Utils-------------//
	////////////////////////////////
	bool						checkValideMode(User &user, std::vector<std::string> &args);
	void						setChannelMode(User &user, std::vector<std::string> &args, Channel &channel);
	void						setChannelModeOperator(User &user, std::vector<std::string> &args, Channel &channel);
	void						setChannelModePrivate(User &user, std::vector<std::string> &args, Channel &channel);
	void						setChannelModeSecret(User &user, std::vector<std::string> &args, Channel &channel);
	void						setChannelModeInvite(User &user, std::vector<std::string> &args, Channel &channel);
	void						setChannelModeTopic(User &user, std::vector<std::string> &args, Channel &channel);
	void						setChannelModeOutside(User &user, std::vector<std::string> &args, Channel &channel);
	void						setChannelModeModerated(User &user, std::vector<std::string> &args, Channel &channel);
	void						setChannelModeLimit(User &user, std::vector<std::string> &args, Channel &channel);
	void						setChannelModeBan(User &user, std::vector<std::string> &args, Channel &channel);
	void						setChannelModeVoice(User &user, std::vector<std::string> &args, Channel &channel);
	void						setChannelModeKey(User &user, std::vector<std::string> &args, Channel &channel);
	void						setUserMode(User &user, std::vector<std::string> &args);
	void						setUserModeInvisible(User &user, std::vector<std::string> &args);
	void						setUserModeNoticed(User &user, std::vector<std::string> &args);
	void						setUserModeWallops(User &user, std::vector<std::string> &args);
	void						setUserModeOperator(User &user, std::vector<std::string> &args);
	void						joinToChannel(User &user, std::string chName, std::string chPass);
	void						createAndJoinToChannel(User &user, std::string chName, std::string chPass);
	////////////////////////////////
	//----------Service-----------//
	////////////////////////////////
	void						sendP2PMsg(User &sender, User& recipient, std::string arg1="", std::string arg2="", std::string arg3="");
	void						sendErrorResponse(unsigned int code, const User &user, std::string arg1="", std::string arg2="");
	void						sendResponse(unsigned int code, const User &user, std::string arg1="", std::string arg2="", \
																std::string arg3="", std::string arg4="", std::string arg5="", \
																std::string arg6="", std::string arg7="");
};

#endif
