#pragma once

#include "irc.hpp"
#include "Channel.hpp"
#include "Client.hpp"

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
