#ifndef SERVICE_HPP
#define SERVICE_HPP

# include <string>
# include <sstream>
# include <sys/time.h>
# include <vector>
# include "../User/User.hpp"

class Service {
public:
	static uint64_t						timer();
	static std::string					getDate();
	static std::vector<std::string>		split(const std::string& str, char delimeter);
	static void			sendErrorResponse(unsigned int code, const User &user, std::string arg1="", std::string arg2="");
	static void			sendResponse(unsigned int code, const User &user, std::string arg1="", std::string arg2="", \
														std::string arg3="", std::string arg4="", std::string arg5="", \
														std::string arg6="", std::string arg7="");
};

#endif