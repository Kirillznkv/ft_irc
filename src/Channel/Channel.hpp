#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include <string>
# include <vector>
# include "../Server/Server.hpp"
# include "../Service/Utils.hpp"

class User;

class Channel {
private:
	typedef std::vector<User>::iterator			iter;
	typedef std::vector<User>::const_iterator	const_iter;

	bool			_inviteOnly;
	bool			_hasPassword;
	bool			_secret;
	bool			_private;
	bool			_noOutside;
	bool			_moderated;
	bool			_topicByOper;
	unsigned int	_userLimit;

	std::string			_topic;
	std::string			_password;
	std::string			_channelName;
	std::vector<User>	_users;
	std::vector<User>	_operators;
	std::vector<User>	_invites;
	std::vector<User>	_voices;
	std::vector<User>	_banList;

	Channel();
public:
	Channel(std::string name, User &user, std::string password = "");
	Channel(const Channel &copy);
	~Channel();
	Channel			&operator=(const Channel &);
	bool			operator==(const Channel &op) const;
	bool					addUser(User &user, std::string password);
	void					addUserToBanList(User &user);
	void					addUserToInviteList(User &user);
	void					addUserToVoiceList(User &user);
	void					addOperator(User &user);
	void					deleteUser(User &user);
	void					deleteOperator(User &user);
	void					sendToAll(User &sender, std::string channelName, std::string msg);
	void					muteAll();
	void					unmuteAll();
	// Отказался от бана всех кроме находящихся (banAllNonMember)

	bool					isInviteOnly() const;
	bool					isPassword() const;
	bool					isTopicByOper() const;
	bool					isSecret() const;
	bool					isPrivate() const;
	bool					isOperator(User &user) const;
	bool 					inChannel(User user) const;
	bool					isUserInvited(User &user) const;
	std::string				getChannelName() const;
	std::string				getChannelTopic() const;
	std::vector<User>&		getBanList();
	std::vector<User>&		getOpers();
	std::vector<User>&		getUsers();
	std::vector<User>&		getInvites();
	std::vector<User>&		getVoices();
	void					setPrivateFlag(bool flag);
	void					setSecretFlag(bool flag);
	void					setInviteFlag(bool flag);
	void					setTopicFlag(bool flag);
	void					setOutsideFlag(bool flag);
	void					setModeratedFlag(bool flag);
	void					setUserLimit(unsigned int limit);
	void					setPassword(std::string pass);
	void					setTopic(std::string topic);
	void					resetPassword();
};

#endif