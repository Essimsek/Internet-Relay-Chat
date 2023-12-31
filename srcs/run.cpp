#include "../inc/Server.hpp"
#include "../inc/Commands.hpp"
#include "../inc/Utils.hpp"

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::istringstream stream(str);
    std::vector<std::string> result;

    std::string token;
    while (getline(stream, token, delimiter)) {
        if (!token.empty())
            result.push_back(token);
    }
    return result;
}

int runCommand(Server &sv, Client &cl, std::vector <std::string> command)
{
    if (command[0] == "JOIN" && command.size() == 2)
        Commands::runJoin(sv, cl, Utils::trimString(command[1]));
    if (command[0] == "PRIVMSG" && command.size() >= 3)
        Commands::runPrivMsg(sv, cl, command);
    if (command[0] == "NOTICE" && command.size() >= 3)
        Commands::runNotice(sv, cl, command);
    if (command[0] == "KICK" && command.size() >= 3)
        Commands::runKick(sv, cl, command);
    if (Utils::trimString(command[0]) == "QUIT" && command.size() == 1)
        Commands::runQuit(sv, cl);
    // ASSADM <chname> <nickName> <text>
    if (command[0] == "ASSADM" && command.size() >= 3)
        Commands::RunAssignAdmin(sv, cl, command);
    return 1;
}

int getClientCommand(Server &sv, Client &cl, std::string buffer)
{
    std::cout << "Client <" << cl.getClientName() << ">: " << buffer << "::" << std::endl;
    std::cout << "AUTH: " << cl.getClientAuth() << std::endl;
    std::vector <std::string> command = splitString(buffer, ' ');
    
    if ((command[0] == "PASS" || command[0] == "PASS\n") && cl.getClientAuth() == NOT_AUTH)
    {
        if (sv.checkPassword(command[1]) == 0 && command.size() == 2)
        {
            cl.setClientAuth(PASS_AUTH);
            cl.sendMessage(":" + std::string(sv.hostname) + " 353 " + cl.getClientName() + " :PASSWORD CORRECT\n");
        }
        else if (command.size() != 2)
            cl.sendMessage(":" + std::string(sv.hostname) + " 464 " + cl.getClientName() + "PASS usage 'PASS <password>'\n");
        else
            cl.sendMessage(":" + std::string(sv.hostname) + " 464 " + cl.getClientName() + " :PASSWORD INCORRECT\n");
    }
    if (command[0] == "NICK" || command[0] == "NICK\n")
    {
        if (cl.getClientAuth() >= PASS_AUTH && command.size() == 2)
        {
			if (command[1][0] == '#') {
				cl.sendMessage(":" + std::string(sv.hostname) + " 451 " + cl.getClientName() + " :Client name cannot start with <#>!\n");
				return 0;
			}
            if (sv.IsAlreadyInUse(Utils::trimString(command[1]), cl))
            {
                cl.setNickName(command[1]);
                cl.setClientAuth(NICK_AUTH);
                cl.sendMessage(":" + std::string(sv.hostname) + " 353 " + cl.getClientName() + " :Nickname is saved\n");
            }
        }
        else if (cl.getClientAuth() == NOT_AUTH)
            cl.sendMessage(":" + std::string(sv.hostname) + " 461 " + cl.getClientName() + " :You must enter password first!\n");
        else
            cl.sendMessage(":" + std::string(sv.hostname) + " 461 " + cl.getClientName() + " :NICK usage 'NICK <nick name>'\n");
    }
    if (command[0] == "USER" || command[0] == "USER\n")
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
            cl.sendMessage(":" + std::string(sv.hostname) + " 461 " + cl.getClientName() + " :You must enter nickname!\n");
        else if (cl.getClientAuth() == NOT_AUTH)
            cl.sendMessage(":" + std::string(sv.hostname) + " 461 " + cl.getClientName() + " :You must enter nickname and password!\n");
        else
            cl.sendMessage(":" + std::string(sv.hostname) + " 461 " + cl.getClientName() + "USER usage 'USER <user name> <host name> <serv name>'\n");
    }
    if (cl.getClientAuth() == AUTH)
        return (runCommand(sv, cl, command));

    return 1;
}