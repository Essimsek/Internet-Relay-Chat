#pragma once

#include "irc.hpp"

class Channel {
    private:
        std::string chName;
        std::map <int, std::string> users;

    public:
        Channel();
        ~Channel();
        

};
