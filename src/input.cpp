#include <iostream>
#include <fstream>
#include <string>
#include "ai.h"

int main()
{
    std::string file = "data.txt";
    std::ifstream read;

    std::cout << "Initializing AI Database\n" << std::endl;

    file = "inputs/" + file;
    read.open(file);
    if(!read)
    {
        std::cout << "Failed to read from file " << file << std::endl;

        return 1;
    }

    std::vector<std::string> reading;

    for(std::string text; getline(read, text); )
    {
        reading.push_back(text);
    }
    read.close();

    AI * container = new AI(reading);

    container->input();

    std::ofstream write;

    write.open(file, std::ofstream::out | std::ofstream::trunc);
    if(!write)
    {
        std::cout << "Failed to save to file " << file << std::endl;

        return 1;
    }
    write.close();

    delete container;

    return 0;
}