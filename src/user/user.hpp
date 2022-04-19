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
	bool    	_validPass;
	bool    	_registered;
	bool    	_admin;
	// int     registerPhase;
	// bool    away;
	// bool    invisible;
	// bool    serv_notices;
	// bool    wallops;
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
	bool 		isAdmin() const;
	bool 		isValidPass() const;
	bool 		isRegistered() const;
	////////////////////////////////
	//----------Setters-----------//
	////////////////////////////////
	void		setId(int id);
	void 		setServerName(std::string serverName);
	void 		setNickName(std::string nickName);
	void		setUserName(std::string userName);
	void 		setRealName(std::string realName);
	void 		setHost(std::string host);
	void 		setRealHost(std::string realHost);
	void		setAdmin(bool b);
	void		setValidPass(bool b);
	void		setRegistered(bool b);
	// void		setSocketFd(int fd);
};

#endif
