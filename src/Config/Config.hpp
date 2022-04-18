#ifndef CONFIG_HPP
#define CONFIG_HPP

# include <string>
# include <fstream>
# include <map>

class Config {
private:
	std::string 						_fileName;
	std::map<std::string, std::string>	_map;
	bool 								_ok;
private:
	Config(const Config &);
	Config &operator=(const Config &);
	void initMap();
	void checkInit();
public:
	Config();
	~Config();
	std::string	operator [](std::string const& name);
	std::string	const operator [](std::string const& name) const;
	bool 		ok() const;
};

#endif
