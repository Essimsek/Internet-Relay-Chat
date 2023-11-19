#include "../../inc/irc.hpp"
#include "../../inc/Commands.hpp"
#include "../../inc/Channel.hpp"

int writeToUser(Server &sv, Client &cl, std::vector <std::string> command) {
    for(std::vector<Client>::iterator it = sv.clients.begin(); it != sv.clients.end(); ++it)
        if (it->getClientName() == command[1])
        {
            it->sendMessage(":" + cl.getClientName() + "!" + cl.username + "@" + cl.hostname + " PRIVMSG " + command[1] + " " + command[2]);
            return 1;
        }
    return 0;
}

void     Commands::runPrivMsg(Server &sv, Client &from, std::vector <std::string> command) {
    //if (isChannel(&sv, command[1]))
    //    writeToChannel(sv, from, command);
    if (writeToUser(sv, from, command))
        std::cout << "Message Sended" << std::endl;
    else
        std::cout << "Message Not Sended" << std::endl;
}