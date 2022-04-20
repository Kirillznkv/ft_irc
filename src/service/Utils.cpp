# include "Utils.hpp"

bool Utils::isUserExist(const std::vector<User> &vec, User &user) {
	typedef std::vector<User>::const_iterator const_iter;
	for (const_iter it = vec.cbegin(); it != vec.cend(); ++it) {
		if (it->getId() == user.getId() || it->getNickName() == user.getNickName())
			return true;
	}
	return false;
}

std::vector<User>::iterator Utils::findUser(std::vector<User> &vec, User &user) {
	std::vector<User>::iterator it = vec.begin();
	while (it != vec.end() && it->getNickName() != user.getNickName())
		++it;
	return it;
}