#include "chat.h"

Chat::Chat(std::vector<std::string> templateInput, std::vector<std::string> responseInput)
{
    templates = templateInput;
    response = responseInput;
}

Chat::~Chat()
{

}