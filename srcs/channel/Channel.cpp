#include "../../inc/Channel.hpp"

Channel::Channel(std::string name, Client founder){
    this->chName = name;
    (this->admins).push_back(founder);
    (this->users).push_back(founder);
}

std::string Channel::getChName() {
    return (this->chName);
}

int Channel::isInChannel(Client &cl) {
	for (std::vector<Client>::iterator itt = this->users.begin(); itt != this->users.end(); itt++)
		if (itt->getClientFd() == cl.getClientFd())
			return 1;
	return 0;
}

int Channel::isAdmin(Client &cl)
{
	for (std::vector<Client>::iterator admin = this->admins.begin(); admin != this->admins.end(); admin++)
	{
		if (admin->getClientFd() == cl.getClientFd())
			return (1);
	}
	return (0);
}

Client	*Channel::isThereMember(std::vector<Client> &clients, Client &admin, std::string &userName)
{
    for (std::vector<Client>::iterator cl = clients.begin(); cl != clients.end(); cl++)
	{
		if (cl->getClientName() == userName && admin.getClientFd() != cl->getClientFd())
			return &(*cl);
	}
	return (NULL); 
}

void Channel::removeClient(Client* client)
{
    for (std::vector<Client>::iterator cl = this->admins.begin(); cl != this->admins.end(); )
    {
        if (cl->getClientName() == client->getClientName())
        {
            cl = this->admins.erase(cl);
        }
        else
            ++cl;
    }

    for (std::vector<Client>::iterator cl = this->users.begin(); cl != this->users.end(); )
    {
        if (cl->getClientFd() == client->getClientFd())
        {
            cl = this->users.erase(cl);
            return;
        }
        else
            ++cl;
    }

    if (this->users.empty())
    {
        ;
        //sv.removeChannel();
    }
    else if (this->admins.empty())
    {
        this->admins.push_back(this->users[0]);
    }
}