#include "../../inc/irc.hpp"
#include "../../inc/Commands.hpp"
#include "../../inc/Channel.hpp"
#include "../../inc/Utils.hpp"

// "KICK usage 'KICK <channel> <user> <text>'"

Client	*isThereMember(std::vector<Client> &users, Client &admin, std::string &userName)
{
	for (std::vector<Client>::iterator cl = users.begin(); cl != users.end(); cl++)
	{
		if (cl->getClientName() == userName && admin.getClientFd() != cl->getClientFd())
			return &(*cl);
	}
	return (NULL);
}

int		isAdmin(std::vector<Client> &admins, Client &cl)
{
	for (std::vector<Client>::iterator admin = admins.begin(); admin != admins.end(); admin++)
	{
		if (admin->getClientFd() == cl.getClientFd())
			return (1);
	}
	return (0);
}

Channel	*isThereChannel(Server &sv, Client &cl, const std::string &chName)
{
    for (std::vector<Channel>::iterator ch = sv.chList.begin(); ch != sv.chList.end(); ++ch)
	{
        if (ch->chName == chName)
            return &(*ch);
    }
    return NULL;
}

void	Commands::runKick(Server &sv, Client &cl, std::vector <std::string> command)
{
	std::string chName = command[1];
	std::string userName = command[2];
	std::string text = Utils::getMessage(command, TEXTSTART);

    Channel* foundChannel = isThereChannel(sv, cl, chName);

    if (foundChannel)
	{
		if (isAdmin(foundChannel->admins, cl))
		{
			Client *client = isThereMember(foundChannel->users, cl, userName);
			if (client)
			{
				client->sendMessage("KICK " + chName + " " + userName + " :" + text);
				foundChannel->removeClient(client);
				return ;
			}
			else
			{
				cl.sendMessage("There is no such user on the channel!\n");
				return ;
			}
		}
		else
		{
			cl.sendMessage("You are not the Admin on this channel!!\n");
			return ;
		}
	} 
	else
        cl.sendMessage("Channel not found\n");
}
