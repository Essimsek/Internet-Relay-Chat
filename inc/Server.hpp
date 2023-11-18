#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <poll.h>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <limits.h>
#include "Client.hpp"
#include "Channel.hpp"

class Server {
    private:
        int serverFd;
        struct sockaddr_in server_address;
        std::string password;
    public:
        Server();
        ~Server();
        void    setUpServer(int port, std::string pw);
        int     getServerFd();
        struct  sockaddr_in getServerAddress();
        int     checkPassword(std::string pw);
        void    getInformation();
        void    addChannel(Channel ch);
        int num_clients;
        std::vector <Channel> chList;
        std::vector <Client> clients;
        char *hostname;
};
