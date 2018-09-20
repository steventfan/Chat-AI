#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <string>
#include <vector>

class Template
{
    public:
        Template(std::vector<std::string>, std::vector<std::string>);
        ~Template();
    private:
        std::vector<std::string> templates;
        std::vector<std::string> response;
};

#endif