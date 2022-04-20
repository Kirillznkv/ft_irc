#include <iostream>
#include "src/Server/Server.hpp"


int     main(int argc, char **argv) {
    if (argc == 3) {
		std::string argv2(argv[2]);
		Server serv(atoi(argv[1]), argv2);
		serv.start();
    }
    else {
        std::cout << "Wrong arguments for launching\n";
        return (1);
    }
    return (0);
}
