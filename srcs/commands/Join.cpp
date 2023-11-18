#include "../../inc/irc.hpp"
#include "../../inc/Commands.hpp"
#include "../../inc/Channel.hpp"


void createNewChannel(Server &sv, Client &cl, std::string chName)
{
    Channel ch(chName, cl);
    sv.chList.push_back(ch);
    cl.sendMessage(":" + cl.getClientName() + "!" + cl.username + "@" + cl.hostname + " JOIN " + chName + "\r\n");
    cl.sendMessage(":" + cl.getClientName() + "!" + cl.username + "@" + cl.hostname + " JOIN " + chName + " +o " + cl.getClientName() + "\r\n");
    cl.sendMessage(":" + cl.getClientName() + "!" + cl.username + "@" + cl.hostname + " JOIN " + chName + "\r\n");
    cl.sendMessage(":" + std::string(sv.hostname) + " 353 " + cl.getClientName() + " = " + chName + " :@" + cl.getClientName()+ "\r\n");
    cl.sendMessage(":" + std::string(sv.hostname) + " 366 " + cl.getClientName() + " " + chName + " :End of /NAMES list\r\n");
    //sv.ch.users.push_back(client)
}
void addToExistingChannel(Server &sv, Client &cl, Channel &ch)
{
    for(std::vector<Client>::iterator it = ch.users.begin(); it != ch.users.end(); ++it)
    {
        if (it->getClientName() == cl.getClientName())
        {
            cl.sendMessage(":" + std::string(sv.hostname) + " 451 " + cl.getClientName() + " :The user already in the channel!\n");
            return;
        }
    }
    ch.users.push_back(cl);
}

void Commands::runJoin(Server &sv, Client &cl, std::string chName)
{
    int a = 0;

    for(std::vector<Channel>::iterator it = sv.chList.begin(); it != sv.chList.end(); ++it) {
        if (chName == it->chName)
        {
            addToExistingChannel(sv, cl, *it);
            a = 1;
        }
    }
    if (a == 0)
        createNewChannel(sv, cl, chName);
}
