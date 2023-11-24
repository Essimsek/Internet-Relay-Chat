#include "../../inc/irc.hpp"
#include "../../inc/Commands.hpp"
#include "../../inc/Channel.hpp"
#include "../../inc/Utils.hpp"

void	Commands::runKick(Server &sv, Client &cl, std::vector <std::string> command)
{
	std::string chName = command[1];
	std::string userName = command[2];
	std::string text = Utils::getMessage(command, TEXTSTART);

    Channel* foundChannel = sv.isThereChannel(cl, chName);
    if (foundChannel)
	{
		if (foundChannel->isAdmin(cl))
		{
			Client *client = foundChannel->isThereMember(foundChannel->users, cl, userName);
			if (client)
			{
				client->sendMessage("KICK " + chName + " " + cl.getClientName() + " :" + text);
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
