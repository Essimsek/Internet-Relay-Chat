#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <poll.h>
#include <cstring>
#include "../inc/Server.hpp"
#define MAX_CLIENTS 16

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
        exit(-1);
    }

    std::string temp;
    char message[64] = "Welcome to IRC-EMOM\n";
    char buffer[64];
    std::string str;
    struct sockaddr_in client_address;
	socklen_t client_len = sizeof(client_address);

    int server_socket, client_sockets[MAX_CLIENTS], num_clients = 0;
    Server sv;
    sv.setUpServer(atoi(av[1]));
    server_socket = sv.getServerFd();
    struct sockaddr_in server_address = sv.getServerAddress();

    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    listen(server_socket, MAX_CLIENTS);
    struct pollfd pollfds[MAX_CLIENTS + 1];
    pollfds[0].fd = server_socket;
    pollfds[0].events = POLLIN;
    pollfds[0].revents = 0;
    while (1)
    {
        int n = poll(&pollfds[0], num_clients + 1, -1);
        if (n < 0)
        {
            std::cout << "POLL ERROR" << std::endl;
            exit(-1);
        }
        if (pollfds[0].revents & POLLIN){
            std::cout << "server istek geldi" << std::endl;
            client_sockets[num_clients] = accept(server_socket, (struct sockaddr *)&client_address, &client_len);
            pollfds[num_clients + 1].fd = client_sockets[num_clients];
            pollfds[num_clients + 1].events = POLLIN;
            send(client_sockets[num_clients], message, sizeof(message), 0);
            num_clients++;
        }
        for (int i = 1; i <= num_clients; i++)
        {
            if (pollfds[i].revents & POLLIN) {
                ssize_t a = recv(client_sockets[i - 1], buffer, sizeof(buffer), 0);
                if (a < 0)
                {
                    std::cout << "error on recv" << std::endl;
                    exit(-1);
                }
                buffer[a] = '\0';   
                temp = std::to_string(i) + ". client: ";
                for (int j = 0; j < num_clients; j++) {
                    send(client_sockets[j], temp.c_str(), sizeof(temp.c_str()), 0);
                    send(client_sockets[j], buffer, sizeof(buffer), 0);
                }
            }
        }
    }
    
}