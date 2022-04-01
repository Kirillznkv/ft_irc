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
	// std::string _realHost;
	// std::string _serverName;
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
	bool operator==(const User &op);
	bool operator!=(const User &op);
	////////////////////////////////
	//----------Getters-----------//
	////////////////////////////////
	int			getId() const;
	int			getSocketFd() const;
	std::string	getNickName() const;
	std::string	getUserName() const;
	std::string	getRealName() const;
	std::string	getHost() const;
	bool 		isAdmin() const;
	bool 		isValidPass() const;
	bool 		isRegistered() const;
	////////////////////////////////
	//----------Setters-----------//
	////////////////////////////////
	int			setId(int id);
	std::string	setNickName(std::string nickName);
	std::string	setUserName(std::string userName);
	std::string	setRealName(std::string realName);
	std::string	setHost(std::string host);
	bool		setAdmin(bool b);
	bool		setValidPass(bool b);
	bool		setRegistered(bool b);
	// int		setSocketFd(int fd);
};

#endif