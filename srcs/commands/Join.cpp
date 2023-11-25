#include "../../inc/irc.hpp"
#include "../../inc/Commands.hpp"
#include "../../inc/Channel.hpp"

void createNewChannel(Server &sv, Client &cl, std::string chName)
{
	if (chName.length() < 2 || chName[0] != '#')
		cl.sendMessage(":" + std::string(sv.hostname) + " 451 " + cl.getClientName() + " :Channel name should start with <#> operator!\n");
	else {
    	Channel ch(chName, cl);
    	sv.chList.push_back(ch);
    	cl.sendMessage(":" + cl.getClientName() + "!" + cl.username + "@" + cl.hostname + " JOIN " + chName + "\r\n");
    	cl.sendMessage(":" + cl.getClientName() + "!" + cl.username + "@" + cl.hostname + " MODE " + chName + " +o " + cl.getClientName() + "\r\n");
	}
}

void addToExistingChannel(Server &sv, Client &cl, Channel &ch)
{
    for(std::vector<Client>::iterator it = ch.users.begin(); it != ch.users.end(); it++)
    {
        if (it->getClientFd() == cl.getClientFd())
        {
            cl.sendMessage(":" + std::string(sv.hostname) + " 451 " + cl.getClientName() + " :The user already in the channel!\n");
            return;
        }
    }
    ch.users.push_back(cl);
    cl.sendMessage(":" + cl.getClientName() + "!" + cl.username + "@" + cl.hostname + " JOIN " + ch.chName + "\r\n");
    for(std::vector<Client>::iterator it = ch.users.begin(); it != ch.users.end(); it++)
    {
        if (it->getClientFd() != cl.getClientFd())
            it->sendMessage(cl.username + " Has joined to channel " + ch.chName + "\n");
    }
}

void Commands::runJoin(Server &sv, Client &cl, std::string chName)
{
    int a = 0;

    for(std::vector<Channel>::iterator it = sv.chList.begin(); it != sv.chList.end(); it++) {
        if (chName == it->chName)
        {
            addToExistingChannel(sv, cl, *it);
            a = 1;
        }
    }
    if (a == 0)
        createNewChannel(sv, cl, chName);
}
