#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <poll.h>
#include <cstring>

class Server {
    private:
        int serverFd;
        struct sockaddr_in server_address;
    public:
        Server();
        ~Server();
        void setUpServer(int port);
        int getServerFd();
        struct sockaddr_in getServerAddress();
        
        std::vector <std::string>chList;
};