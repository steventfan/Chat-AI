#ifndef AI_H
#define AI_H

#include <string>
#include <vector>

class AI;
class Template;
class Word;

class AI
{
    public:
        AI(const std::vector<std::string> &);
        ~AI();
    private:
        std::vector<Template *> data;
};

class Template
{
    friend class AI;
    private:
        Template(std::string);
        ~Template();
        std::vector<std::string> templates;
        std::vector<std::string> response;
        std::vector<Word *> words;
};

class Word
{
    friend class AI;
    friend class Template;
    private:
        Word(std::string);
        std::string word;
        unsigned int count;
};

#endif