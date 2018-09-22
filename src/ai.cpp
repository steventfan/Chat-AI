#include "ai.h"
#include <iostream>

AI::AI(const std::vector<std::string> & reading)
{
    bool templates = true;
    unsigned int dataAt = 0;

    for(unsigned int readingAt = 0; readingAt < reading.size(); readingAt++)
    {
        if(reading.at(readingAt) == "*")
        {
            for(unsigned int templatesAt = 0; templatesAt < data.at(dataAt)->templates.size(); templatesAt++)
            {
                std::size_t found;
                unsigned int index = 0;

                while( (found = data.at(dataAt)->templates.at(templatesAt).find(' ', index) ) != std::string::npos)
                {
                    unsigned int wordsAt;

                    for(wordsAt = 0; wordsAt < data.at(dataAt)->words.size(); wordsAt++)
                    {
                        if(data.at(dataAt)->templates.at(templatesAt).substr(index, found - index) == data.at(dataAt)->words.at(wordsAt)->word)
                        {
                            data.at(dataAt)->words.at(wordsAt)->count++;

                            break;
                        }
                    }
                    if(wordsAt >= data.at(dataAt)->words.size() )
                    {
                        data.at(dataAt)->words.push_back(new Word(data.at(dataAt)->templates.at(templatesAt).substr(index, found - index) ) );
                    }
                    index = found + 1;
                }
                if(index < data.at(dataAt)->templates.at(templatesAt).size() )
                {
                    unsigned int wordsAt;

                    for(wordsAt = 0; wordsAt < data.at(dataAt)->words.size(); wordsAt++)
                    {
                        if(data.at(dataAt)->templates.at(templatesAt).substr(index, data.at(dataAt)->templates.at(templatesAt).size() - index) == data.at(dataAt)->words.at(wordsAt)->word)
                        {
                            data.at(dataAt)->words.at(wordsAt)->count++;

                            break;
                        }
                    }
                    if(wordsAt >= data.at(dataAt)->words.size() )
                    {
                        data.at(dataAt)->words.push_back(new Word(data.at(dataAt)->templates.at(templatesAt).substr(index, data.at(dataAt)->templates.at(templatesAt).size() - index) ) );
                    }
                }
            }
            templates = false;

            continue;
        }
        else if(reading.at(readingAt) == "-")
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