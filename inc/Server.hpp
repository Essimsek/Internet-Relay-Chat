#pragma once

#include "irc.hpp"
#include "Channel.hpp"
#include "Client.hpp"

#define MAX_CLIENTS 64

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
        int     IsAlreadyInUse(std::string nickName, Client &cl);
        Channel *isThereChannel(Client &cl, const std::string &chName);


        int     num_clients;
        std::vector <Channel> chList;
        std::vector <Client> clients;
        char hostname[64];
        struct pollfd pollfds[MAX_CLIENTS + 1];
};

int getClientCommand(Server &sv, Client &cl, std::string buffer);
