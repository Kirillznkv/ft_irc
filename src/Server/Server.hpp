#ifndef SERVER_HPP
#define SERVER_HPP

# include <iostream>
# include <vector>
# include <map>
# include <string>
# include <sstream>
# include <fstream>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include "../User/User.hpp"
# include "../Config/Config.hpp"
# include "../Service/ParseRequest.hpp"
# include "../Channel/Channel.hpp"

class Channel;
class User;

class Server
{
public:
	struct PingData {
		std::string serverName;
		std::string userNickName;
		uint64_t lastMessageTime;
		uint64_t responseTimeout;
		uint64_t requestTimeout;
		int socket;
		bool responseWaiting;
		bool restartRequest;
		bool restartResponse;
		bool isOnline;
		bool disconnect;
		PingData();
		~PingData();
	};
private:
	typedef std::vector<User>::iterator			iter_user;
	typedef std::vector<Channel>::iterator		iter_channel;
	typedef std::vector<std::string>::iterator	iter_str;
	unsigned short int			_port;
	std::string					_pass;
	fd_set						_fdRead;
	uint64_t					_responseTimeout;
	uint64_t					_requestTimeout;
	int							_maxClients;
	int							_socketFd, _newSocketFd, _maxFd;
	std::map<int, PingData>		_pingData;
	std::vector<User>			_users;
	std::vector<User>			_usersHistory;
	std::vector<Channel>		_channels;
	Config						_conf;
public:
	Server(unsigned short int port, std::string pass);
	~Server();
	void		start();
	static void	sendSocket(int socketFd, std::string response);
private:
	////////////////////////////////
	//----------Server------------//
	////////////////////////////////
	void			newUserConnect();
	void			readSocket();
	void			execRequest(User &user, std::string buf);
	std::string		accepting();
	bool			settingUpSocket();
	void			init();
	void			kickUserFromChannel(User &user, iter_channel channel);
	void			killUser(User &user);
	void			createPingTread(User &user);
	void			clearAll();
	////////////////////////////////
	//----------Commands----------//
	////////////////////////////////
	void	adminCmd(User &user, std::vector<std::string> &args);// Done
	void	awayCmd(User &user, std::vector<std::string> &args);// Done
	void	infoCmd(User &user, std::vector<std::string> &args);// Done
	void	inviteCmd(User &user, std::vector<std::string> &args);// Done
	void	isonCmd(User &user, std::vector<std::string> &args);// Done
	void	joinCmd(User &user, std::vector<std::string> &args);// Done
	void	kickCmd(User &user, std::vector<std::string> &args);// Done
	void	killCmd(User &user, std::vector<std::string> &args);// Done
	void	listCmd(User &user, std::vector<std::string> &args);// Done
	void	modeCmd(User &user, std::vector<std::string> &args);// Done
	void	motdCmd(User &user);// Done
	void	namesCmd(User &user, std::vector<std::string> &args);// Done
	void	nickCmd(User &user, std::vector<std::string> &args);// Done
	void	noticeCmd(User &user, std::vector<std::string> &args);// Done
	void	operCmd(User &user, std::vector<std::string> &args);// Done
	void	partCmd(User &user, std::vector<std::string> &args);// Done
	void	passCmd(User &user, std::vector<std::string> &args);// Done
	void	pingCmd(User &user, std::vector<std::string> &args);// Done
	void	pongCmd(User &user, std::vector<std::string> &args);// Done
	void	privMsgCmd(User &user, std::vector<std::string> &args);// Done
	void	quitCmd(User &user);// Done
	void	rehashCmd(User &user);// Done
	void	restartCmd(User &user);// Done
	void	timeCmd(User &user, std::vector<std::string> &args);// Done
	void	topicCmd(User &user, std::vector<std::string> &args);// Done
	void	userCmd(User &user, std::vector<std::string> &args);// Done
	void	versionCmd(User &user, std::vector<std::string> &args);// Done
	void	wallopsCmd(User &user, std::vector<std::string> &args);// Done
	void	whoCmd(User &user, std::vector<std::string> &args);// Done
	void	whoisCmd(User &user, std::vector<std::string> &args);// Done
	void	whoWasCmd(User &user, std::vector<std::string> &args);// Done
	void			chooseCommand(User &user, std::vector<std::string> &args);
	void			process(User &user, std::string req);
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
	std::vector<User>			strToUsers(const std::string& str, User &usrWhoAsk);
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
