# include "Utils.hpp"

uint64_t Utils::timer() {
	static struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / (uint64_t)1000));
}

std::string Utils::getDate() {
	time_t timetoday;
	time(&timetoday);
	// string result = asctime(localtime(&timetoday));
	// return result.substr(0, result.length() - 1);
	return asctime(localtime(&timetoday)); // Может быть стоит выделить память
}

std::vector<std::string> Utils::split(const std::string& str, char delimeter) {
	std::vector<std::string> args;
	std::istringstream f(str);
	std::string s;
	while (getline(f, s, delimeter))
		args.push_back(s);
	return args;
}

bool Utils::isValidChannelName(std::string chName) {
	if (chName == "")
		return false;
	if (Channel::isChannelName(chName) == false)
		return false;
	for (size_t i = 1; i < chName.length(); i++)
		if ((chName[i] < 'a' || chName[i] > 'z') && (chName[i] < 'A' || chName[i] > 'Z') && (chName[i] < '0' || chName[i] > '9') && chName[i] != '_')
			return false;
    return true;
}

bool Utils::isUserExist(const std::vector<User> &vec, std::string nickName) {
	typedef std::vector<User>::const_iterator const_iter;
	for (const_iter it = vec.cbegin(); it != vec.cend(); ++it) {
		if (it->getNickName() == nickName)
			return true;
	}
	return false;
}

std::vector<User>::iterator Utils::findUser(std::vector<User> &vec, std::string nickName) {
	std::vector<User>::iterator it = vec.begin();
	while (it != vec.end() && it->getNickName() != nickName)
		++it;
	return it;
}

bool Utils::isChannelExist(const std::vector<Channel> &vec, std::string chName) {
	typedef std::vector<Channel>::const_iterator const_iter;
	for (const_iter it = vec.cbegin(); it != vec.cend(); ++it) {
		if (it->getChannelName() == chName)
			return true;
	}
	return false;
}

std::vector<Channel>::iterator Utils::findChannel(std::vector<Channel> &vec, std::string chName) {
	std::vector<Channel>::iterator it = vec.begin();
	while (it != vec.end() && it->getChannelName() != chName)
		++it;
	return it;
}

std::string Utils::getUsers(Channel &channel) {
	typedef std::vector<User>::iterator iter;
	std::string result;
	for (iter it = channel.getUsers().begin(); it != channel.getUsers().end(); ++it)
		if (channel.isOperator(*it))
			result += "@" + it->getNickName() + " ";
	for (iter it = channel.getUsers().begin(); it != channel.getUsers().end(); ++it)
		if (channel.isOperator(*it) == false)
			result += it->getNickName() + " ";
	if (result.size())
		result.pop_back();
	return result;
}
