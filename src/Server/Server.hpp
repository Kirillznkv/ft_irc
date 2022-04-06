#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include "../User/User.hpp"
#include "../Service/Service.hpp"
#include <vector>

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


// Kirills comments
	bool isTruePass(std::string pass) const;
	void killUser(User &user) const;

	std::vector<User>	_users;
private:
	friend class Service;
	Service				_service;
};

#endif