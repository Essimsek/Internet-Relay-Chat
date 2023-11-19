#include "../inc/irc.hpp"
#include "../inc/Client.hpp"
#include "../inc/Server.hpp"


class Commands {
    private:

    public:
        static void     runJoin(Server &sv, Client &cl, std::string chName);

};