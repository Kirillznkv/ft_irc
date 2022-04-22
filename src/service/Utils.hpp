#ifndef UTILS_HPP
#define UTILS_HPP

# include <vector>
# include "../User/User.hpp"

class User;
class Channel;

class Utils {
public:
	static uint64_t							timer();
	static std::string						getDate();
	static std::vector<std::string>			split(const std::string& str, char delimeter);
	static bool								isValidChannelName(std::string chName);
	static bool								isUserExist(const std::vector<User> &vec, std::string nickName);
	static bool								isChannelExist(const std::vector<Channel> &vec, std::string chName);
	static std::vector<User>::iterator		findUser(std::vector<User> &vec, std::string nickName);
	static std::vector<Channel>::iterator	findChannel(std::vector<Channel> &vec, std::string chName);
	static std::string						getUsers(Channel &channel);
};

#endif