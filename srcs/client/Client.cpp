#include "../../inc/Client.hpp"

Client::Client(int server_socket, int num_clients){
    this->username = "client_" + std::to_string(num_clients);
    this->nickname = "client_" + std::to_string(num_clients);
    this->auth = NOT_AUTH;
    this->clientLen = sizeof(this->clAddress);
    this->clientFd = accept(server_socket, (struct sockaddr *)&(this->clAddress), &this->clientLen);
}

Client::~Client() {}

std::string Client::getClientName() {
    return ((this->nickname).substr(0, (this->nickname).size()-2));
}

int Client::getClientFd() {
    return (this->clientFd);
}

struct sockaddr_in Client::getClientAddress() {
    return (this->clAddress);
}

int Client::getClientAuth() {
    return (this->auth);
}

void Client::setClientAuth(int i) {
    this->auth = i;
}

void Client::sendMessage(std::string message)
{
    send(this->clientFd, message.c_str(), strlen(message.c_str()), 0);
}

void Client::setNickName(std::string nickname)
{
    this->nickname = nickname;
}

void Client::setUserName(std::string username){
    this->username = username;
}