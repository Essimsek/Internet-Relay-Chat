#include "../../inc/Server.hpp"

Server::Server() {}

Server::~Server() {}

int Server::getServerFd() {
	return (this->serverFd);
}

void Server::setUpServer(int port, const std::string password){
	this->serverFd = socket(AF_INET, SOCK_STREAM, 0);
	this->password = password;
	(this->server_address).sin_family = AF_INET;
	(this->server_address).sin_port = htons(port);
	(this->server_address).sin_addr.s_addr = INADDR_ANY;
}

void Server::getInformation()
{
	std::cout<<"Server Password   : "<<this->password<<std::endl;
	std::cout<<"Server Fd         : "<<this->serverFd<<std::endl;
	std::cout<<"Server sin port   : "<<(this->server_address).sin_port<<std::endl;
	std::cout<<"Server sin family : "<<static_cast<int>((this->server_address).sin_family) << std::endl;
	std::cout<<"Server sin address: "<<(this->server_address).sin_addr.s_addr<<std::endl;
}

struct sockaddr_in Server::getServerAddress(){
	return (this->server_address);
}