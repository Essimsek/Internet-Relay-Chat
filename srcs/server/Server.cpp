#include "../../inc/Server.hpp"

Server::Server() {
    this->num_clients = 0;
}

Server::~Server() {}

int Server::getServerFd() {
    return (this->serverFd);
}

void Server::setUpServer(int port, std::string pw) {
    this->password = pw;
    this->serverFd = socket(AF_INET, SOCK_STREAM, 0);
    (this->server_address).sin_family = AF_INET;
    (this->server_address).sin_port = htons(port);
    (this->server_address).sin_addr.s_addr = INADDR_ANY;

    std::cout << "PORT: " << port << std::endl;
    std::cout << "PASSWORD: " << pw << std::endl;
}

struct sockaddr_in Server::getServerAddress(){
    return (this->server_address);
}

int Server::checkPassword(std::string pw)
{
    pw = pw.substr(0, pw.size()-1);
    return (pw.compare(this->password));
}