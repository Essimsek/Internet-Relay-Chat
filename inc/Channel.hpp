#pragma once

#include "irc.hpp"
#include "Client.hpp"

class Channel {
	public:
		Channel();
		Channel(std::string name, Client founder);
		std::string chName;
		std::vector <Client> users;
		std::vector <Client> admins;
		std::string getChName();
		int			isInChannel(Client &cl);
		void        removeClient(Client* client);
		int         isAdmin(Client &cl);
		Client		*isThereMember(std::vector <Client> &clients, Client &admin, std::string &userName);

};
