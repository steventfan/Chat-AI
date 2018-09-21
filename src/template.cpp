#include "template.h"

Template::Template(std::vector<std::string> templateInput, std::vector<std::string> responseInput)
{
    templates = templateInput;
    response = responseInput;
    
    unsigned int index = 0;

    while( (std::size_t found = templates.at(0).find(' ', index) ) != std::string::npos)
    {
        if(index < found)
        {
            words.push_back(templates.at(0).substr(index, found - index - 1) );
        }
        index = found + 1;
    }
    if(index < templates.at(0).size() )
    {
        words.push_back(templates.at(0).substr(index, templates.at(0).size() - index) );
    }
}

Template::~Template()
{

}