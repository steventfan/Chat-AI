#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    std::cout << "Initializing AI Database" << std::endl;

    std::ifstream data;

    data.open("inputs/data.txt");
    if(!data)
    {
        std::cout << "Failed to open file data.txt" << std::endl;

        return 1;
    }

    return 0;
}