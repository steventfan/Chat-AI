#include <iostream>
#include <fstream>
#include <string>
#include "ai.h"

int main()
{
    std::string file = "data.txt";
    std::ifstream read;

    std::cout << "[Initializing AI Database]\n" << std::endl;

    file = "inputs/" + file;
    read.open(file);
    if(!read)
    {
        std::cout << "[ERROR] Failed to read from file " << file << std::endl;

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
    std::cout << "\n[Saving AI Database]\n" << std::endl;

    std::ofstream write;

    write.open(file, std::ofstream::out | std::ofstream::trunc);
    if(!write)
    {
        std::cout << "[ERROR] Failed to save to file " << file << std::endl;

        return 1;
    }
    for(unsigned int i = 0; i < container->size(); i++)
    {
        int index = 0;

        while(index >= 0)
        {
            write << container->save(i, true, index) << '\n';
        }
        write << "-\n";
        index = 0;
        while(index >= 0)
        {
            std::string line = container->save(i, false, index);

            if(index >= -1)
            {
                write << line << '\n';
            }
        }
        write << "*\n";
    }
    write.close();

    std::cout << "[AI Database Save Successful]" << std::endl;

    delete container;

    return 0;
}