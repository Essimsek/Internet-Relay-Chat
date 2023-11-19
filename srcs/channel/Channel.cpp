#include "../../inc/Channel.hpp"

Channel::Channel(std::string name, Client founder){
    this->chName = name;
    (this->admins).push_back(founder);
    (this->users).push_back(founder);
}

std::string Channel::getChName() {
    return (this->chName);
}
