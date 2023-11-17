#include "../inc/Server.hpp"

std::vector<std::string> splitString(std::string str, char splitter){
    std::vector<std::string> result;
    std::string current = ""; 
    for(int i = 0; i < str.size(); i++){
        if(str[i] == splitter){
            if(current != ""){
                result.push_back(current);
                current = "";
            } 
            continue;
        }
        current += str[i];
    }
    if(current.size() != 0)
        result.push_back(current);
    return result;
}

int runCommand(Server sv, Client cl, std::vector <std::string> command)
{
    std::cout << "here" << std::endl;
    return 1;
}

int getClientCommand(Server sv, Client cl, std::string buffer)
{
    std::cout << "Client <" << cl.getClientName() << ">: " << buffer << std::endl;
    std::vector <std::string> command = splitString(buffer, ' ');
    
    if (cl.getClientAuth() == AUTH)
        return (runCommand(sv, cl, command));
    if (command[0] == "PASS" && command.size() == 2 && cl.getClientAuth() == NOT_AUTH)
    {
        if (sv.checkPassword(command[1]) == 0)
        {
            cl.setClientAuth(PASS_AUTH);
            cl.sendMessage(":OMERLUTFU 451 omerl :PASSWORD CORRECT\n");
        }
        else
            cl.sendMessage(":OMERLUTFU 451 omerl :PASSWORD INCORRECT\n");
    }
    if (command[0] == "NICK" && command.size() == 2 && cl.getClientAuth() == PASS_AUTH)
    {
        cl.setNickName(command[1]);
        cl.setClientAuth(NICK_AUTH);
    }
    if (command[0] == "USER" && command.size() >= 4 && cl.getClientAuth() == NICK_AUTH)
    {
        cl.username = command[1];
        cl.hostname = command[2];
        cl.servername = command[3];
        cl.setClientAuth(AUTH);
        cl.sendMessage(":OMERLUTFU 451 omerl :Welcome to karsimIRC\n");
    }
    return 1;
}