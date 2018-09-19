#ifndef CHAT_H
#define CHAT_H

#include <string>
#include <vector>

class Chat
{
    public:
        Chat(std::vector<std::string>, std::vector<std::string>);
        ~Chat();
    private:
        std::vector<std::string> templates;
        std::vector<std::string> response;
};

#endif