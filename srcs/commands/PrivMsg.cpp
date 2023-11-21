#include "../../inc/irc.hpp"
#include "../../inc/Commands.hpp"
#include "../../inc/Channel.hpp"
#include "../../inc/Utils.hpp"

int writeToUser(Server &sv, Client &cl, std::vector <std::string> command) {
    std::string msg = Utils::getMessage(command);
    for(std::vector<Client>::iterator it = sv.clients.begin(); it != sv.clients.end(); ++it)
        if (it->getClientName() == command[1] && it->getClientFd() != cl.getClientFd())
        {
            it->sendMessage(":" + cl.getClientName() + "!" + cl.username + "@" + cl.hostname + " PRIVMSG " + command[1] + " " + msg);
            return 1;
        }
    return 0;
}

void writeToChannel(Server &sv, Client &from, std::vector <std::string> command) {
	std::string msg;
	msg = Utils::getMessage(command);

    int control = 0;
	for(std::vector<Channel>::iterator it = sv.chList.begin(); it != sv.chList.end(); ++it)
	{
        if (command[1] == it[0].chName && it->isInChannel(from))
        {
            for (std::vector<Client>::iterator itt = it->users.begin(); itt != it->users.end(); ++itt)
                if (itt->getClientFd() != from.getClientFd())
                    itt->sendMessage(":" + from.getClientName() + "!" + from.username + "@" + from.hostname + " PRIVMSG " + command[1] + " " + msg);
            control = 1;                    
			break;
        }
	}
    if (control == 0)
        from.sendMessage("No channel found\n");
    else
        return;
}

void     Commands::runPrivMsg(Server &sv, Client &from, std::vector <std::string> command) {
	if (command[1][0] == '#')
		writeToChannel(sv, from, command);
	else if(writeToUser(sv, from, command))
		;
	else
		from.sendMessage("No client found\n");
}
