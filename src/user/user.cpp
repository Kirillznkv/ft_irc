#include "user.hpp"

////////////////////////////////
//----------Constructs--------//
////////////////////////////////
User::User(int socketFd) : _socketFd(socketFd) {}
User::~User() {}
User::User(const User &copy) {
	this->operator=(copy);
}

////////////////////////////////
//----------Opertors----------//
////////////////////////////////
User &User::operator=(const User &op) {
	if (this != &op) {
		_id = op.getId();
		_socketFd = op.getSocketFd();
		_nickName = op.getNickName();
		_userName = op.getUserName();
		_realName = op.getRealName();
		_host = op.getHost();
		_validPass = op.isValidPass();
		_registered = op.isRegistered();
		_admin = op.isAdmin();
	}
	return *this;
}
bool User::operator==(const User &op) { return _id == op.getId(); }
bool User::operator!=(const User &op) { return _id != op.getId(); }

////////////////////////////////
//----------Getters-----------//
////////////////////////////////
int			User::getId() const { return _id; }
int			User::getSocketFd() const { return _socketFd; }
std::string	User::getNickName() const { return _nickName; }
std::string	User::getUserName() const { return _userName; }
std::string	User::getRealName() const { return _realName; }
std::string	User::getHost() const { return _host; }
bool 		User::isAdmin() const { return _admin; }
bool 		User::isValidPass() const { return _validPass; }
bool 		User::isRegistered() const { return _registered; }

////////////////////////////////
//----------Setters-----------//
////////////////////////////////
int			User::setId(int id) { _id = id; }
std::string	User::setNickName(std::string nickName) { _nickName = nickName; }
std::string	User::setUserName(std::string userName) { _userName = userName; }
std::string	User::setRealName(std::string realName) { _realName = realName; }
std::string	User::setHost(std::string host) { _host = host; }
bool		User::setAdmin(bool b) { _admin = b; }
bool		User::setValidPass(bool b) { _validPass = b; }
bool		User::setRegistered(bool b) { _registered = b; }
// int		User::setSocketFd(int fd) { _socketFd = fd; }