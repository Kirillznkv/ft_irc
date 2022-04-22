#include "User.hpp"

unsigned int User::_amountUsers = 0;

////////////////////////////////
//----------Constructs--------//
////////////////////////////////
User::User(int socketFd)
	: _id(_amountUsers++), _socketFd(socketFd),
	_validPass(false), _registered(false), _admin(false) {}
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
bool User::operator==(const User &op) const { return _id == op.getId(); }
bool User::operator!=(const User &op) const { return _id != op.getId(); }

////////////////////////////////
//----------Getters-----------//
////////////////////////////////
int			User::getId() const { return _id; }
int			User::getSocketFd() const { return _socketFd; }
std::string	User::getServerName() const { return _serverName; }
std::string	User::getNickName() const { return _nickName; }
std::string	User::getUserName() const { return _userName; }
std::string	User::getRealName() const { return _realName; }
std::string	User::getHost() const { return _host; }
std::string	User::getRealHost() const { return _realHost; }
std::string	User::getAutoReply() const { return _autoReply; }
bool 		User::isAdmin() const { return _admin; }
bool 		User::isAway() const { return _away; }
bool 		User::isValidPass() const { return _validPass; }
bool 		User::isRegistered() const { return _registered; }
std::vector<Channel>	&User::getJoinedChannels() { return _joinedChannels; }

////////////////////////////////
//----------Setters-----------//
////////////////////////////////
void 		User::setServerName(std::string serverName) { _serverName = serverName; }
void 		User::setNickName(std::string nickName) { _nickName = nickName; }
void 		User::setUserName(std::string userName) { _userName = userName; }
void 		User::setRealName(std::string realName) { _realName = realName; }
void 		User::setHost(std::string host) { _host = host; }
void 		User::setRealHost(std::string realHost) { _realHost = realHost; }
void 		User::setAutoReply(std::string autoReply) { _autoReply = autoReply; }
void		User::setAdmin(bool flag) { _admin = flag; }
void		User::setAway(bool flag) { _away = flag; }
void		User::setValidPass(bool flag) { _validPass = flag; }
void		User::setRegistered(bool flag) { _registered = flag; }
void		User::setSocketFd(int fd) { _socketFd = fd; }
