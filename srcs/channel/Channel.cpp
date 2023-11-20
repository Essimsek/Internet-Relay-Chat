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
		if (itt->getClientName() == cl.getClientName())
			return 1;
	return 0;
}