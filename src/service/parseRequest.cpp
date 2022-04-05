#include "parseRequest.hpp"

bool ParseRequest::emptyRequest(std::string req) { return req == "\n"; }

std::vector<std::string> ParseRequest::strToWordsVector(std::string str) {
	std::vector<std::string> target;
	std::istringstream f(str);
	std::string buf;
	while (getline(f, buf, ' ')) {
		if (!buf.empty())
			target.push_back(buf);
	}
	return target;
}

std::string ParseRequest::getPrefix(std::vector<std::string> &args) {
	std::string prefix;
	if (args.front()[0] == ':') {
		args.front().erase(0, 1);
		prefix = args.front();
		args.erase(args.begin());
	}
	return prefix;
}

void ParseRequest::printRequestData(std::string prefix, const std::vector<std::string> &args) {
	printf("prefix: <%s>, ", prefix.c_str());
	printf("command: <%s>, ", args[0].c_str());
	for (std::vector<std::string>::const_iterator it = args.begin() + 1;  it != args.end(); ++it)
		printf(" (%s)", (*it).c_str());
	std::cout << std::endl;
}

std::vector<std::string> ParseRequest::parseRequest(std::string req) {
	std::vector<std::string> args = ParseRequest::strToWordsVector(req);
	std::string prefix = ParseRequest::getPrefix(args);
	ParseRequest::printRequestData(prefix, args);
	return args;
}