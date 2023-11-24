#include "../../inc/Server.hpp"
#include "../../inc/Commands.hpp"
#include "../../inc/Utils.hpp"
#include "../../inc/Client.hpp"

Server::Server() {
    this->num_clients = 0;
}

Server::~Server() {}

int Server::getServerFd() {
    return (this->serverFd);
}

void Server::setUpServer(int port, std::string pw) {
    this->password = pw;
    this->num_clients = 0;
    this->serverFd = socket(AF_INET, SOCK_STREAM, 0);
    (this->server_address).sin_family = AF_INET;
    (this->server_address).sin_port = htons(port);
    (this->server_address).sin_addr.s_addr = INADDR_ANY;
    gethostname(this->hostname, 64);
}

struct sockaddr_in Server::getServerAddress(){
    return (this->server_address);
}

void Server::getInformation()
{
    std::cout<<"Server Password   : "<< this->password<<" Password Length: "<<this->password.length()<< std::endl;
    std::cout<<"Server Hostname   : "<<this->hostname<<std::endl;
    std::cout<<"Server Fd         : "<<this->serverFd<<std::endl;
    std::cout<<"Server port       : "<<ntohs((this->server_address).sin_port)<<std::endl;
    std::cout<<"Server family     : "<<static_cast<int>((this->server_address).sin_family) << std::endl;
    std::cout<<"Server address    : "<<(this->server_address).sin_addr.s_addr<<std::endl;
}

Channel*	Server::isThereChannel(Client &cl, const std::string &chName)
{
    for (std::vector<Channel>::iterator ch = this->chList.begin(); ch != this->chList.end(); ++ch)
	{
        if (ch->chName == chName)
            return &(*ch);
    }
    return NULL;
}

int Server::checkPassword(std::string pw)
{
    pw = Utils::trimString(pw);
    return (pw.compare(this->password));
}

int Server::IsAlreadyInUse(std::string nickName, Client &cl)
{
    for (std::vector<Client>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
    {
        if (it->getClientName() == nickName)
        {
            cl.sendMessage(":" + std::string(this->hostname) + " 433 " + ":" + nickName + " :Nickname is already in use\n");
            return (0);
        }
    }
    return (1);
}
