#include "../../inc/Utils.hpp"

namespace Utils {
    std::string trimString(const std::string& string) {
        size_t pos = string.find_first_of("\t\r\n");
        if (pos != std::string::npos)
            return (string.substr(0, pos));
        return string;
    }
}

namespace Utils {
    std::string getMessage(const std::vector<std::string> &strings, int msgPos) {
        std::string result;
        for (int i = msgPos; i < strings.size(); ++i) {
            result += strings[i];
            if (i < strings.size() - 1) {
                result += " ";
            }
        }
        return result;
    }
}
