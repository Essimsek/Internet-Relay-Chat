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
    result += "\n";
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

int writeToallUsers();

void     Commands::runPrivMsg(Server &sv, Client &from, std::vector <std::string> command) {
    int control;
    std::string msg;

    control = 0;    
    for(std::vector<Channel>::iterator it = sv.chList.begin(); it != sv.chList.end(); ++it)
    {
        std::cout<<"Trying to find channel name dude!!"<<std::endl;
        if (command[1] == it[0].chName)
        {
            msg = getMessage(command);
            for (std::vector<Client>::iterator itt = it[0].users.begin(); itt != it[0].users.end(); ++itt)
                if (itt[0].getClientFd() != from.getClientFd())
                    itt->sendMessage(":" + from.getClientName() + "!" + from.username + "@" + from.hostname + " PRIVMSG " + command[1] + " " + msg);
            control = 1;
            std::cout<<"Channel name found!"<<std::endl;
            break;
        }
    }

    if (control == 0) {
        if (writeToUser(sv, from, command)) {
            std::cout << "Message Sended" << std::endl;
        }
    } else {
        std::cout << "Message Not Sended" << std::endl;
    }
}