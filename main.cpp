#include <iostream>
#include "src/Server/Server.hpp"


int     main(int argc, char **argv) {
    if (argc == 3) {
    	try {
			std::string argv2(argv[2]);
			Server serv(atoi(argv[1]), argv2);
			serv.start();
		} catch (const char *s) {
    		std::cerr<<s<<std::endl;
    		return (1);
    	}
    }
    else {
        std::cout << "Wrong arguments for launching:\n";
        std::cout << "./ircserv <port> <password>\n";
        return (1);
    }
    return (0);
}
