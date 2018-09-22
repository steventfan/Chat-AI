#include <iostream>
#include <fstream>
#include <string>
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

    container->input();

    delete container;

    return 0;
}