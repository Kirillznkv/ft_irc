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

std::string Utils::getFlags(Channel &channel) {
	std::string res;
	if (channel.isInviteOnly())
		res += 'i';
	if (channel.isModerated())
		res += 'm';
	if (channel.isTopicByOper())
		res += 't';
	if (channel.isNotOutside())
		res += 'n';
	if (channel.isPrivate())
		res += 'p';
	if (channel.isPassword())
		res += 'k';
	if (res.size() > 0)
		res = "[+" + res + "]";
	return res;
}

std::string Utils::getChannels(User &userWhoAsk, User &user) {
	typedef std::vector<Channel>::iterator iter;
	std::string res;
	for (iter itChannel = user.getJoinedChannels().begin(); itChannel != user.getJoinedChannels().end(); ++itChannel) {
		if (itChannel->isSecret() == false) {
			if (itChannel->isPrivate() == false || itChannel->inChannel(userWhoAsk)) {
				if (Utils::isUserExist(itChannel->getOpers(), user.getNickName()))
					res += "[@]";
				res += Utils::getFlags(*itChannel) + itChannel->getChannelName() + ' ';
			} else
				res += "Prv ";
		} else if (itChannel->inChannel(userWhoAsk)) {
			if (Utils::isUserExist(itChannel->getOpers(), user.getNickName()))
				res += "[@]";
			res += Utils::getFlags(*itChannel) + itChannel->getChannelName() + ' ';
		}
	}
	if (res.empty() == false)
		res.pop_back();
	return res;
}

std::string Utils::getLastChannel(User &user) {
	std::vector<Channel> channels = user.getJoinedChannels();
	if (channels.size() == 0)
		return "*no joined channels*";
	Channel channel = channels[channels.size() - 1];
	if (channel.isSecret())
		return "Scr";
	if (channel.isPrivate())
		return "Prv";
	return channel.getChannelName();
}
