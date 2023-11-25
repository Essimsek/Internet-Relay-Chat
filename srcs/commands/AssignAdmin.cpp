#include "../../inc/irc.hpp"
#include "../../inc/Commands.hpp"
#include "../../inc/Channel.hpp"
#include "../../inc/Utils.hpp"

void	Commands::RunAssignAdmin(Server &sv, Client &cl, std::vector<std::string> command)
{
	std::string chName = command[1];
	std::string userName = command[2];
	std::string text = Utils::getMessage(command, TEXTSTART);

	Channel* foundChannel = sv.isThereChannel(cl, chName);
	if (foundChannel)
	{
		if (foundChannel->isAdmin(cl))
		{
			// Check if there is user and the user is not already admin
			Client *client = foundChannel->isThereMember(foundChannel->users, cl, userName);
			if (client && !foundChannel->isThereMember(foundChannel->admins, cl, userName))
			{
				foundChannel->admins.push_back(*client);
				client->sendMessage("ASSADM " + chName + " " + userName + " :" + text);
				client->sendMessage(":" + client->getClientName() + "!" + client->username + "@" + client->hostname + " MODE " + chName + " +o " + client->getClientName() + "\r\n");
				return ;
			}
			else
			{
				cl.sendMessage("The user already admin or not in the channel\n");
				return ;
			}
		}
		else
		{
			cl.sendMessage("Only admins can assign another admin!!\n");
			return ;
		}
	}
	else
		cl.sendMessage("Channel not found\n");
}
