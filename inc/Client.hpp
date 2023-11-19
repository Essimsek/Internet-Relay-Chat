#pragma once

#include "irc.hpp"

#define NOT_AUTH 0
#define PASS_AUTH 1
#define NICK_AUTH 2
#define AUTH 3

class Client {
    private:
        std::string nickname;
        int clientFd;
        int auth;
        socklen_t clientLen;
        struct sockaddr_in clAddress;
    public:
        Client(int server_socket, int num_clients);
        ~Client();
        std::string getClientName();
        int getClientFd();
        int getClientAuth();
        void setClientAuth(int i);
        struct sockaddr_in getClientAddress();
        void sendMessage(std::string message);
        void setNickName(std::string nickname);
        void setUserName(std::string username);

        std::string hostname;
        std::string username;
        std::string servername;

};