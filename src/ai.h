#ifndef AI_H
#define AI_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

class AI;
class Data;
class Templates;
class Word;

class AI
{
    public:
        AI(const std::vector<std::string> &);
        ~AI();
        void input();
        std::string save(unsigned int, bool, int &);
        unsigned int size();
    private:
        std::vector<Data *> data;
};

class Data
{
    friend class AI;
    private:
        Data(std::string, std::vector<std::string> &);
        ~Data();
        std::vector<Templates *> templates;
        std::vector<std::string> response;
        std::vector<Word *> words;
};

class Templates
{
    friend class AI;
    friend class Data;
    private:
        Templates(std::string, std::vector<std::string> &);
        std::string line;
        std::vector<std::string> tokens;
};

class Word
{
    friend class AI;
    friend class Data;
    private:
        Word(std::string);
        std::string word;
        unsigned int count;
};

#endif