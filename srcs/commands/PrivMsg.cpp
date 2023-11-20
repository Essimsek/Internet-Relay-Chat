#include "../../inc/irc.hpp"
#include "../../inc/Commands.hpp"
#include "../../inc/Channel.hpp"

#define MSGSTART 2

std::string getMessage(const std::vector<std::string> &strings) {
    std::string result;
    for (int i = MSGSTART; i < strings.size(); ++i) {
        result += strings[i];
        if (i < strings.size() - 1) {
            result += " ";
        }
    }
    return result;
}

int writeToUser(Server &sv, Client &cl, std::vector <std::string> command) {
    std::string msg = getMessage(command);
    for(std::vector<Client>::iterator it = sv.clients.begin(); it != sv.clients.end(); ++it)
        if (it->getClientName() == command[1])
        {
            it->sendMessage(":" + cl.getClientName() + "!" + cl.username + "@" + cl.hostname + " PRIVMSG " + command[1] + " " + msg);
            return 1;
        }
    return 0;
}

void writeToChannel(Server &sv, Client &from, std::vector <std::string> command) {
	std::string msg;
	msg = getMessage(command);

	for(std::vector<Channel>::iterator it = sv.chList.begin(); it != sv.chList.end(); ++it)
	{
        if (command[1] == it[0].chName && it->isInChannel(from))
        {
            for (std::vector<Client>::iterator itt = it->users.begin(); itt != it->users.end(); ++itt)
                if (itt->getClientFd() != from.getClientFd())
                    itt->sendMessage(":" + from.getClientName() + "!" + from.username + "@" + from.hostname + " PRIVMSG " + command[1] + " " + msg);
			break;
        }
	}
}

void     Commands::runPrivMsg(Server &sv, Client &from, std::vector <std::string> command) {
	if (command[1][0] == '#')
		writeToChannel(sv, from, command);
	else if(writeToUser(sv, from, command))
		;
	else
		from.sendMessage("No channel or client found\n");
}