#ifndef UTILS_HPP
#define UTILS_HPP

# include <vector>
# include "../User/User.hpp"

class User;

class Utils {
public:
	static bool							isUserExist(const std::vector<User> &vec, User &user);
	static std::vector<User>::iterator	findUser(std::vector<User> &vec, User &user);
};

#endif