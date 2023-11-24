#pragma once

#include "irc.hpp"

namespace Utils {
    std::string trimString(const std::string& str);
    std::string getMessage(const std::vector<std::string> &strings, int msgPos);
    std::vector<std::string> splitString(const std::string& str, char delimiter);
}
