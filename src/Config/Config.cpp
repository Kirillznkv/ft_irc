#include "Config.hpp"

Config::Config() : _fileName("src/config.conf") { initMap(); }
Config::~Config() {}

void Config::initMap() {
	std::ifstream file;
	file.open (_fileName, std::ifstream::in);
	if (file.is_open() == false)
		return ;
	std::string line;
	while (getline(file, line)) {
		if (line.find(":") == std::string::npos)
			return ;
		_map.insert(std::make_pair(line.substr(0, line.find(':')), line.substr(line.find(':') + 2)));
	}
	file.close();
	checkInit();
}

void Config::checkInit() {
	if (_map.empty())
		return ;
	bool ok = true;
	std::string need[] = {
			"name", "version", "debugLevel",
			"release", "mail", "author",
			"operators", "compilationTime",
			"maxConnections", "maxChannels",
			"requestTimeout", "responseTimeout"
	};
	for (int i = 0; i < need->size(); ++i)
		if (_map.find(need[i]) == _map.end())
			ok = false;
	_ok = ok;
}

bool Config::ok() const { return _ok; }

std::string Config::operator [](std::string const& name) {
	return (_ok && _map.find(name) != _map.end()) ? _map.find(name)->second : "";
}

std::string const Config::operator [](std::string const& name) const {
	return (_ok && _map.find(name) != _map.end()) ? _map.find(name)->second : "";
}