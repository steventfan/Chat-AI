#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    std::string file = "data.txt";
    std::ifstream data;

    std::cout << "Initializing AI Database" << std::endl;

    file = "inputs/" + file;
    data.open(file);
    if(!data)
    {
        std::cout << "Failed to open file data.txt" << std::endl;

        return 1;
    }

    return 0;
}