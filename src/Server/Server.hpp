#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include "../User/User.hpp"

class Server
{
private:
    int                         fd;
    unsigned short int          port;
    unsigned long               ipAddr;

public:
    Server();
    ~Server();

    std::vector<User>    user;

    void    createConnection();

};

#endif