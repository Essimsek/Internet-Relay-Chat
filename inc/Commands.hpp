#include "irc.hpp"
#include "Client.hpp"
#include "Server.hpp"


class Commands {
	private:

	public:
		static void         runJoin(Server &sv, Client &cl, std::string chName);
		static void         runPrivMsg(Server &sv, Client &from, std::vector <std::string> command);
		static void         runKick(Server &sv, Client &cl, std::vector <std::string> command);
		static void			runNotice(Server &sv, Client &from, std::vector <std::string> command);
		static void 		runQuit(Server &sv, Client &cl);
		static void			RunAssignAdmin(Server &sv, Client &cl, std::vector<std::string> command);
};
