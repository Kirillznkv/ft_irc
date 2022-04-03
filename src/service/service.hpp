#ifndef SERVICE_HPP
#define SERVICE_HPP

# include <string>
# include "../user/user.hpp"

class Service {
public:
	static void	sendErrorResponse(unsigned int code, const User &user, std::string arg1, std::string arg2);
	static void	sendResponse(unsigned int code, const User &user, std::string arg1, std::string arg2, std::string arg3, \
												std::string arg4, std::string arg5, std::string arg6, std::string arg7);
};

#endif