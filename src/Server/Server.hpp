#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include "../user/user.hpp"
#include "../Channel/Channel.hpp" //this is right???

class Server
{
private:
    int                         fd;
    unsigned short int          port;
    unsigned long               ipAddr;

public:
    Server();
    ~Server();

    std::vector<User>       users;
    std::vector<Channel>    channels;

    void    createConnection();

};

#endif