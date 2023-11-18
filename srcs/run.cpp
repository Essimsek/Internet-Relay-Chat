#include "../inc/Server.hpp"

void    is_contain(std::string str, char c)
{
    if (str.find(c) != std::string::npos)
        std::cout << "The string contains :"<<c<< std::endl;
    else
        std::cout << "The string not contains :"<<c<< std::endl;
}

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::istringstream stream(str);
    std::vector<std::string> result;

    std::string token;
    while (getline(stream, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

/*
int runCommand(Server sv, Client cl, std::vector <std::string> command)
{
    std::cout << "here" << std::endl;
    if (command[0] == "JOIN" && command.size() == 2);
    //    runJoin(sv, cl, command);
    if (command[0] == "PRIVMSG" && command.size() >= 3);
        //runPrivMsg(cl);
    return 1;
}
*/

int getClientCommand(Server &sv, Client &cl, std::string buffer)
{
    std::cout << "Client <" << cl.getClientName() << ">: " << buffer << "::" << std::endl;
    std::cout << "AUTH: " << cl.getClientAuth() << std::endl;
    std::vector <std::string> command = splitString(buffer, ' ');
    
    //if (cl.getClientAuth() == AUTH)
        //return (runCommand(sv, cl, command));
    if (command[0] == "PASS" && cl.getClientAuth() == NOT_AUTH)
    {
        if (sv.checkPassword(command[1]) == 0)
        {
            cl.setClientAuth(PASS_AUTH);
            cl.sendMessage(":" + std::string(sv.hostname) + " 001 " + cl.getClientName() + " :PASSWORD CORRECT\n");
        }
        else if (command.size() != 2)
            cl.sendMessage(":" + std::string(sv.hostname) + " 464 " + cl.getClientName() + "PASS usage 'PASS <password>'\n");
        else
            cl.sendMessage(":" + std::string(sv.hostname) + " 464 " + cl.getClientName() + " :PASSWORD INCORRECT\n");
    }
    if (command[0] == "NICK")
    {
        if (cl.getClientAuth() == PASS_AUTH && command.size() == 2)
        {
            cl.setNickName(command[1]);
            cl.setClientAuth(NICK_AUTH);
            cl.sendMessage(":" + std::string(sv.hostname) + " 001 " + cl.getClientName() + " :Nickname is saved\n");
        }
        else if (cl.getClientAuth() == NOT_AUTH)
            cl.sendMessage(":" + std::string(sv.hostname) + " 000 " + cl.getClientName() + " :You must enter password first!\n");
        else
            cl.sendMessage(":" + std::string(sv.hostname) + " 461 " + cl.getClientName() + " :NICK usage 'NICK <nick name>'\n");
    }
    if (command[0] == "USER")
    {
        if (cl.getClientAuth() == NICK_AUTH && command.size() >= 4)
        {
            cl.username = command[1];
            cl.hostname = command[2];
            cl.servername = command[3];
            cl.setClientAuth(AUTH);
            cl.sendMessage(":" + std::string(sv.hostname) + " 001 " + cl.getClientName() + " :Welcome to karsimIRC\n");
        }
        else if (cl.getClientAuth() == PASS_AUTH)
            cl.sendMessage(":" + std::string(sv.hostname) + " 000 " + cl.getClientName() + " :You must enter nickname!\n");
        else if (cl.getClientAuth() == NOT_AUTH)
            cl.sendMessage(":" + std::string(sv.hostname) + " 000 " + cl.getClientName() + " :You must enter nickname and password!\n");
        else
            cl.sendMessage(":" + std::string(sv.hostname) + " 461 " + cl.getClientName() + "USER usage 'USER <user name> <host name> <serv name>'\n");
    }
    return 1;
}