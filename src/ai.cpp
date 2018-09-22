#include "ai.h"

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
                for(unsigned int wordAt = 0; wordAt < data.at(dataAt)->words.size(); wordAt++)
                {
                    for(unsigned int tokenAt = 0; tokenAt < data.at(dataAt)->templates.at(templatesAt).size(); tokenAt++)
                    {
                        if(data.at(dataAt)->words.at(wordAt)->word == data.at(dataAt)->templates.at(templatesAt).at(tokenAt) )
                        {
                            data.at(dataAt)->words.at(wordAt)->count++;

                            break;
                        }
                    }
                }
                for(unsigned int tokenAt = 0; tokenAt < data.at(dataAt)->templates.at(templatesAt).size(); tokenAt++)
                {
                    unsigned int wordAt;

                    for(wordAt = 0; wordAt < data.at(dataAt)->words.size(); wordAt++)
                    {
                        if(data.at(dataAt)->templates.at(templatesAt).at(tokenAt) == data.at(dataAt)->words.at(wordAt)->word)
                        {
                            break;
                        }
                    }
                    if(wordAt >= data.at(dataAt)->words.size() )
                    {
                        data.at(dataAt)->words.push_back(new Word(data.at(dataAt)->templates.at(templatesAt).at(tokenAt) ) );
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
            std::vector<std::string> line;

            std::size_t found;
            unsigned int index = 0;

            while( (found = reading.at(readingAt).find(' ', index) ) != std::string::npos)
            {
                line.push_back(reading.at(readingAt).substr(index, found - index) );

                index = found + 1;
            }
            if(index < reading.at(readingAt).size() )
            {
                line.push_back(reading.at(readingAt).substr(index, reading.at(readingAt).size() - index) );
            }
            if(dataAt >= data.size() )
            {
                data.push_back(new Template(line) );
            }
            else
            {
                data.at(dataAt)->templates.push_back(line);
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
    for(unsigned int dataAt = 0; dataAt < data.size(); dataAt++)
    {
        delete data.at(dataAt);
    }
}

void AI::input()
{
    srand(data.size() % 9999);

    std::string text;

    std::cout << "> ";
    while(getline(std::cin, text) )
    {
        if(text == "/exit")
        {
            break;
        }
        else if(text.size() == 0 || text.at(0) == '/')
        {
            std::cout << "[CHAT AI] >>> [INVALID INPUT]\n> ";

            continue;
        }
        for(int i = 0; i < int(text.size() ); i++)
        {
            if( (text.at(i) < 'A' && text.at(i) != ' ') || (text.at(i) > 'Z' && text.at(i) < 'a') || text.at(i) > 'z')
            {
                text.erase(i, 1);
                i--;
            }
        }
        for(unsigned int i = 0; i < text.size(); i++)
        {
            if(text.at(i) >= 'A' && text.at(i) <= 'Z')
            {
                text.at(i) = int(text.at(i) ) + 32;
            }
        }

        std::size_t found;
        int index = 0;
        std::vector<std::string> input;

        while( (found = text.find(' ', index) ) != std::string::npos)
        {
            input.push_back(text.substr(index, found - index) );
            index = found + 1;
        }
        if(index < int(text.size() ) )
        {
            input.push_back(text.substr(index, text.size() - index) );
        }

        double tolerance = 0.75;
        double max = 0;

        index = -1;
        for(unsigned int dataAt = 0; dataAt < data.size(); dataAt++)
        {
            for(unsigned int templatesAt = 0; templatesAt < data.at(dataAt)->templates.size(); templatesAt++)
            {
                unsigned int count = 0;

                for(unsigned int tokenAt = 0; tokenAt < data.at(dataAt)->templates.at(templatesAt).size(); tokenAt++)
                {
                    for(unsigned int inputAt = 0; inputAt < input.size(); inputAt++)
                    {
                        if(data.at(dataAt)->templates.at(templatesAt).at(tokenAt) == input.at(inputAt) )
                        {
                            count++;
                        }
                    }
                }

                double value = double(count) / double(data.at(dataAt)->templates.at(templatesAt).size() );

                for(unsigned int wordsAt = 0; wordsAt < data.at(dataAt)->words.size(); wordsAt++)
                {
                    unsigned int inputAt;

                    for(inputAt = 0; inputAt < input.size(); inputAt++)
                    {
                        if(data.at(dataAt)->words.at(wordsAt)->word == input.at(inputAt) )
                        {
                            value += 0.01 * data.at(dataAt)->words.at(wordsAt)->count;

                            break;
                        }
                    }
                    if(inputAt >= input.size() )
                    {
                        value -= 0.01 * data.at(dataAt)->words.at(wordsAt)->count;
                    }
                }
                if(value >= tolerance && value > max)
                {
                    max = value;
                    index = dataAt;
                }
            }
        }
        if(index > -1 && data.at(index)->response.size() > 0)
        {
            std::cout << "[CHAT AI] >>> " << data.at(index)->response.at(rand() % data.at(index)->response.size() ) << std::endl;
            if(max < 1.00)
            {
                data.at(index)->templates.push_back(input);
            }
        }
        else
        {
            if(index == -1)
            {
                data.push_back(new Template(input) );
                index = data.size() - 1;
            }
            std::cout << "[CHAT AI] >>> [INPUT RESPONSE]\n>: ";
            getline(std::cin, text);
            if(text.size() == 0 || text.at(0) == '/')
            {
                std::cout << "[CHAT AI] >>> [RESPONSE REDACTED]\n> ";

                continue;
            }
            data.at(index)->response.push_back(text);
            std::cout << "[CHAT AI] >>> [RESPONSE RECORDED] " << data.at(index)->response.at(0) << std::endl;
        }
        std::cout << "> ";
    }

    return;
}

Template::Template(std::vector<std::string> & templates)
{
    this->templates.push_back(templates);
}

Template::~Template()
{
    for(unsigned int wordsAt = 0; wordsAt < words.size(); wordsAt++)
    {
        delete words.at(wordsAt);
    }
}

Word::Word(std::string word)
{
    this->word = word;
    count = 1;
}