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
	for (std::vector<Client>::iterator itt = this->users.begin(); itt != this->users.end(); ++itt)
		if (itt->getClientFd() == cl.getClientFd())
			return 1;
	return 0;
}

void Channel::removeClient(Client* client)
{
    for (std::vector<Client>::iterator cl = this->users.begin(); cl != this->users.end(); ++cl)
    {
        if (cl->getClientFd() == client->getClientFd())
        {
            this->users.erase(cl);
            return;
        }
    }
    for (std::vector<Client>::iterator cl = this->admins.begin(); cl != this->admins.end(); ++cl)
    {
        if (cl->getClientFd() == client->getClientFd())
        {
            this->admins.erase(cl);
            return;
        }
    }
    if (this->users.size() == 0);
        //sv.removeChannel();
    else if (this->admins.size() == 0)
        this->admins.push_back(this->users[0]);
}
