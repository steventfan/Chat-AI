#include "ai.h"
#include <iostream>

void AI::test()
{
    for(unsigned int i = 0; i < data.size(); i++)
    {
        std::cout << "Number: " << i << std::endl;
        std::cout << "Templates:" << std::endl;
        for(unsigned int j = 0; j < data.at(i)->templates.size(); j++)
        {
            std::cout << data.at(i)->templates.at(j) << std::endl;
        }
        std::cout << "Response:" << std::endl;
        for(unsigned int j = 0; j < data.at(i)->response.size(); j++)
        {
            std::cout << data.at(i)->response.at(j) << std::endl;
        }
        std::cout << "Words:" << std::endl;
        for(unsigned int j = 0; j < data.at(i)->words.size(); j++)
        {
            std::cout << data.at(i)->words.at(j)->word << ' ' << data.at(i)->words.at(j)->count << std::endl;
        }
        std::cout << std::endl;
    }
}

AI::AI(const std::vector<std::string> & reading)
{
    bool templates = true;
    unsigned int dataAt = 0;

    for(unsigned int readingAt = 0; readingAt < reading.size(); readingAt++)
    {
        if(reading.at(readingAt) == "-")
        {
            for(unsigned int templatesAt = 0; templatesAt < data.at(dataAt)->templates.size(); templatesAt++)
            {
                std::size_t found;
                unsigned int index = 0;
                std::vector<std::string> tokens;

                while( (found = data.at(dataAt)->templates.at(templatesAt).find(' ', index) ) != std::string::npos)
                {
                    tokens.push_back(data.at(dataAt)->templates.at(templatesAt).substr(index, found - index) );

                    index = found + 1;
                }
                if(index < data.at(dataAt)->templates.at(templatesAt).size() )
                {
                    tokens.push_back(data.at(dataAt)->templates.at(templatesAt).substr(index, data.at(dataAt)->templates.at(templatesAt).size() ) );
                }
                for(unsigned int wordsAt = 0; wordsAt < data.at(dataAt)->words.size(); wordsAt++)
                {
                    for(unsigned int tokensAt = 0; tokensAt < tokens.size(); tokensAt++)
                    {
                        if(data.at(dataAt)->words.at(wordsAt)->word == tokens.at(tokensAt) )
                        {
                            data.at(dataAt)->words.at(wordsAt)->count++;

                            break;
                        }
                    }
                }
                for(unsigned int tokensAt = 0; tokensAt < tokens.size(); tokensAt++)
                {
                    unsigned int wordsAt;

                    for(wordsAt = 0; wordsAt < data.at(dataAt)->words.size(); wordsAt++)
                    {
                        if(tokens.at(tokensAt) == data.at(dataAt)->words.at(wordsAt)->word)
                        {
                            break;
                        }
                    }
                    if(wordsAt >= data.at(dataAt)->words.size() )
                    {
                        data.at(dataAt)->words.push_back(new Word(tokens.at(tokensAt) ) );
                    }
                }
            }
            templates = false;

            continue;
        }
        else if(reading.at(readingAt) == "*")
        {
            dataAt++;
            templates = true;

            continue;
        }
        if(templates)
        {
            if(dataAt >= data.size() )
            {
                data.push_back(new Template(reading.at(readingAt) ) );
            }
            else
            {
                data.at(dataAt)->templates.push_back(reading.at(readingAt) );
            }
        }
        else
        {
            data.at(dataAt)->response.push_back(reading.at(readingAt) );
        }
    }
}

AI::~AI()
{

}

Template::Template(std::string templates)
{
    this->templates.push_back(templates);
}

Template::~Template()
{

}

Word::Word(std::string word)
{
    this->word = word;
    count = 1;
}