#include "../inc/Server.hpp"

#define MAX_CLIENTS 32

int getClientCommand(Server &sv, Client &cl, std::string buffer);

void ft_error(std::string str)
{
    std::cout << str << std::endl;
    exit(-1);
}

int main(int ac, char **av)
{

    if (ac != 3)
        ft_error("Usage: ./ircserv <port> <password>");
    
    // Linux = HOST_NAME_MAX macos = _SC_HOST_NAME_MAX both of them equal = 72
    char buffer[72];
    //std::vector <Client> cls;
    char hostname[72];
    gethostname(hostname, 64);
    Server sv;
    sv.setUpServer(atoi(av[1]), av[2]);
    sv.hostname = hostname;
    int server_socket = sv.getServerFd();
    sv.getInformation();
    struct sockaddr_in server_address = sv.getServerAddress();

    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    listen(server_socket, MAX_CLIENTS);

    struct pollfd pollfds[MAX_CLIENTS + 1];
    pollfds[0].fd = server_socket;
    pollfds[0].events = POLLIN;
    pollfds[0].revents = 0;
    while (1)
    {
        int n = poll(&pollfds[0], sv.num_clients + 1, -1);
        if (n < 0)
            ft_error("POLL ERROR");
        if (pollfds[0].revents & POLLIN){
            std::cout << "server istek geldi" << std::endl;
            Client cl(server_socket, sv.num_clients);
            pollfds[sv.num_clients + 1].fd = cl.getClientFd();
            pollfds[sv.num_clients + 1].events = POLLIN;
            sv.clients.push_back(cl);
            sv.num_clients++;
        }
        for (int i = 1; i <= sv.num_clients; i++)
        {
            if (pollfds[i].revents & POLLIN) {
                ssize_t a = recv(sv.clients[i - 1].getClientFd(), buffer, sizeof(buffer), 0);
                if (a < 0)
                    ft_error("RECEIVE ERROR");
                buffer[a] = '\0';
                getClientCommand(sv, sv.clients[i - 1], buffer);
            }
        }
    }
    
}