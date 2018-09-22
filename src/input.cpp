#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ai.h"

int main()
{
    std::string file = "data.txt";
    std::ifstream data;

    std::cout << "Initializing AI Database\n" << std::endl; 

    file = "inputs/" + file;
    data.open(file);
    if(!data)
    {
        std::cout << "Failed to open file data.txt" << std::endl;

        return 1;
    }

    std::vector<std::string> reading;

    for(std::string text; getline(data, text); )
    {
        reading.push_back(text);
    }
    data.close();

    AI * container = new AI(reading);

    // for(unsigned int i = 0; i < container->data.size(); i++)
    // {
    //     std::cout << "Number: " << i << std::endl;
    //     std::cout << "Templates:" << std::endl;
    //     for(unsigned int j = 0; j < container->data.at(i)->templates.size(); j++)
    //     {
    //         std::cout << container->data.at(i)->templates.at(j) << std::endl;
    //     }
    //     std::cout << "Response:" << std::endl;
    //     for(unsigned int j = 0; j < container->data.at(i)->response.size(); j++)
    //     {
    //         std::cout << container->data.at(i)->response.at(j) << std::endl;
    //     }
    //     std::cout << "Words:" << std::endl;
    //     for(unsigned int j = 0; j < container->data.at(i)->words.size(); j++)
    //     {
    //         std::cout << container->data.at(i)->words.at(j)->word << ' ' << container->data.at(i)->words.at(j)->count << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}