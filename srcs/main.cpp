#include "../inc/Server.hpp"
#include "../inc/Commands.hpp"

#define MAX_CLIENTS 64

int getClientCommand(Server &sv, Client &cl, std::string buffer);

Server sv;

void ft_error(std::string str)
{
    std::cout << str << std::endl;
    exit(-1);
}

int mainLoop() {
    struct pollfd pollfds[MAX_CLIENTS + 1];
    ssize_t a;
    char buffer[128];

    pollfds[0].fd = sv.getServerFd();
    pollfds[0].events = POLLIN;
    pollfds[0].revents = 0;
    while (1)
    {
        int n = poll(&pollfds[0], sv.num_clients + 1, -1);
        if (n < 0)
            ft_error("POLL ERROR");
        if (pollfds[0].revents & POLLIN){
            Client cl(sv.getServerFd(), sv.num_clients);
            pollfds[sv.num_clients + 1].fd = cl.getClientFd();
            pollfds[sv.num_clients + 1].events = POLLIN;
            sv.clients.push_back(cl);
            sv.num_clients++;
        }
        for (int i = 1; i <= sv.num_clients; i++)
        {
            if (pollfds[i].revents & POLLIN) {
                a = recv(sv.clients[i - 1].getClientFd(), buffer, sizeof(buffer), 0);
                if (a < 0)
                {
                    std::cout << "Client: " << i - 1 << std::endl;
                    ft_error("RECEIVE ERROR");
                }
                else if (a == 0)
                {
                    Commands::runQuit(sv, sv.clients[i - 1]);
                    continue;
                }
                buffer[a] = '\0';
                getClientCommand(sv, sv.clients[i - 1], buffer);
            }
        }
    }
}

int main(int ac, char **av)
{
    if (ac != 3)
        ft_error("Usage: ./ircserv <port> <password>");
    
    sv.setUpServer(atoi(av[1]), av[2]);
    sv.getInformation();

    struct sockaddr_in server_address = sv.getServerAddress();

    bind(sv.getServerFd(), (struct sockaddr*) &server_address, sizeof(server_address));
    listen(sv.getServerFd(), MAX_CLIENTS);

    mainLoop();

    return 0;    
}