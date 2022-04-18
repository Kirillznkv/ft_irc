#include <iostream>
#include "src/Server/Server.hpp"


int     main(int argc, char **argv) {
	if (argv)
		;
    if (argc == 3) {
		Server serv(6667, "pass");
		serv.start();
    }
    else {
        std::cout << "Wrong arguments for launching\n";
        return (1);
    }
    return (0);
}
