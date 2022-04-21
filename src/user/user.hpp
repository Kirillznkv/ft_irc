#ifndef USER_HPP
#define USER_HPP

# include <string>

class User {
private:
	int			_id;
	int			_socketFd;
	std::string _nickName;
	std::string _userName;
	std::string _realName;
	std::string _host;
	std::string _realHost;
	std::string _serverName;
	std::string _autoReply;
	bool		_validPass;
	bool		_registered;
	bool		_admin;
	// int     registerPhase;
	bool		_away;
	// bool    invisible;
	// bool    serv_notices;
	// bool    wallops;
	static unsigned int		_amountUsers;
public:
	User(int socketFd);
	User(const User &copy);
	~User();
	User &operator=(const User &op);
	bool operator==(const User &op) const;
	bool operator!=(const User &op) const;
	////////////////////////////////
	//----------Getters-----------//
	////////////////////////////////
	int			getId() const;
	int			getSocketFd() const;
	std::string	getServerName() const;
	std::string	getNickName() const;
	std::string	getUserName() const;
	std::string	getRealName() const;
	std::string	getHost() const;
	std::string	getRealHost() const;
	std::string	getAutoReply() const;
	bool 		isAdmin() const;
	bool 		isAway() const;
	bool 		isValidPass() const;
	bool 		isRegistered() const;
	////////////////////////////////
	//----------Setters-----------//
	////////////////////////////////
	void 		setServerName(std::string serverName);
	void 		setNickName(std::string nickName);
	void		setUserName(std::string userName);
	void 		setRealName(std::string realName);
	void 		setHost(std::string host);
	void 		setRealHost(std::string realHost);
	void 		setAutoReply(std::string autoReply);
	void		setAdmin(bool flag);
	void		setAway(bool flag);
	void		setValidPass(bool flag);
	void		setRegistered(bool flag);
	void		setSocketFd(int fd);
};

#endif
