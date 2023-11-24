#include "../inc/Server.hpp"
#include "../inc/Commands.hpp"

Server sv;

void ft_error(std::string str)
{
    std::cout << str << std::endl;
    exit(-1);
}

int mainLoop(void) {
    ssize_t a;
    char buffer[128];

    sv.pollfds[0].fd = sv.getServerFd();
    sv.pollfds[0].events = POLLIN;
    sv.pollfds[0].revents = 0;
    while (1)
    {
        int n = poll(&sv.pollfds[0], sv.num_clients + 1, -1);
        if (n < 0)
            ft_error("POLL ERROR");
        if (sv.pollfds[0].revents & POLLIN){
            Client cl(sv.getServerFd(), sv.num_clients);
            sv.pollfds[sv.num_clients + 1].fd = cl.getClientFd();
            sv.pollfds[sv.num_clients + 1].events = POLLIN;
            sv.clients.push_back(cl);
            sv.num_clients++;
        }
        for (int i = 1; i <= sv.num_clients; i++)
        {
            if (sv.pollfds[i].revents & POLLIN) {
                a = recv(sv.clients[i - 1].getClientFd(), buffer, sizeof(buffer), 0);
                if (a < 0)
                {
                    std::cout << "Client: " << i - 1 << std::endl;
                    ft_error("RECEIVE ERROR");
                }
                else if (a == 0)
                {
                    Commands::runQuit(sv, sv.clients[i - 1]);
                    //close(sv.pollfds[i].fd);
                    sv.pollfds[i].fd = -1;
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

    if (bind(sv.getServerFd(), (struct sockaddr*) &server_address, sizeof(server_address)) < 0)
        ft_error("BIND ERROR");
    if (listen(sv.getServerFd(), MAX_CLIENTS) < 0)
        ft_error("LISTEN ERROR");

    mainLoop();

    return 0;    
}