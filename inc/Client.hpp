#pragma once

#include "Server.hpp"

#define NOT_AUTH 0
#define PASS_AUTH 1
#define USER_AUTH 2
#define NICK_AUTH 3
#define AUTH 4

class Client {
    private:
        std::string nickname;
        int clientFd;
        int auth;
        socklen_t clientLen;
        struct sockaddr_in clAddress;
    public:
        Client(int server_socket);
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