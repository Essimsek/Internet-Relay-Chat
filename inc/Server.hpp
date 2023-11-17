#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <poll.h>
#include <cstring>
#include <vector>

class Server {
	private:
		int			serverFd;
		std::string password;
		struct sockaddr_in server_address;
	public:
		Server();
		~Server();
		void	setUpServer(int port, std::string password);
		int		getServerFd();

		// For debuging
		void	getInformation();

		struct	sockaddr_in getServerAddress();
		
		std::vector <std::string>chList;
};