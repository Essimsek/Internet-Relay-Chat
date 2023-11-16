#include "../../inc/Server.hpp"

Server::Server() {}

Server::~Server() {}

int Server::getServerFd() {
    return (this->serverFd);
}

void Server::setUpServer(int port){
    this->serverFd = socket(AF_INET, SOCK_STREAM, 0);
    (this->server_address).sin_family = AF_INET;
    (this->server_address).sin_port = htons(port);
    (this->server_address).sin_addr.s_addr = INADDR_ANY;
}

struct sockaddr_in Server::getServerAddress(){
    return (this->server_address);
}