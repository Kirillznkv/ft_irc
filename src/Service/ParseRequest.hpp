#ifndef PARSEREQUEST_HPP
#define PARSEREQUEST_HPP

# include <string>
# include <sstream>
# include <iostream>
# include <vector>

class ParseRequest {
private:
	static void 					printRequestData(std::string prefix, const std::vector<std::string> &argv);
	static std::string				getPrefix(std::vector<std::string> &argv);
	static std::vector<std::string>	strToWordsVector(std::string req);
public:
	static bool						emptyRequest(std::string req);
	static std::vector<std::string>	parseRequest(std::string req);
};

#endif
