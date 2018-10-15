#include "ai.h"

AI::AI(const std::vector<std::string> & input)
{
    std::vector<std::string> reading = input;
    for(unsigned int readingAt = 0; readingAt < reading.size(); readingAt++)
    {
        bool templates = true;

        if(reading.at(readingAt) == "-")
        {
            templates = false;
        }
        else if(reading.at(readingAt) == "*")
        {
            templates = true;
        }
        else if(templates)
        {
            for(int stringAt = 0; stringAt < int(reading.at(readingAt).size() ); stringAt++)
            {
                if( (reading.at(readingAt).at(stringAt) < 'A' && reading.at(readingAt).at(stringAt) != ' ') || (reading.at(readingAt).at(stringAt) > 'Z' && reading.at(readingAt).at(stringAt) < 'a') || reading.at(readingAt).at(stringAt) > 'z')
                {
                    reading.at(readingAt).erase(stringAt, 1);
                    stringAt--;
                }
                else if(reading.at(readingAt).at(stringAt) >= 'A' && reading.at(readingAt).at(stringAt) <= 'Z')
                {
                    reading.at(readingAt).at(stringAt) = int(reading.at(readingAt).at(stringAt) ) + 32;
                }
            }
        }
    }

    bool templates = true;
    unsigned int dataAt = 0;

    for(unsigned int readingAt = 0; readingAt < reading.size(); readingAt++)
    {
        if(reading.at(readingAt) == "-")
        {
            for(unsigned int templatesAt = 0; templatesAt < data.at(dataAt)->templates.size(); templatesAt++)
            {
                for(unsigned int wordsAt = 0; wordsAt < data.at(dataAt)->words.size(); wordsAt++)
                {
                    for(unsigned int tokenAt = 0; tokenAt < data.at(dataAt)->templates.at(templatesAt)->tokens.size(); tokenAt++)
                    {
                        if(data.at(dataAt)->words.at(wordsAt)->word == data.at(dataAt)->templates.at(templatesAt)->tokens.at(tokenAt) )
                        {
                            data.at(dataAt)->words.at(wordsAt)->count++;

                            break;
                        }
                    }
                }
                for(unsigned int tokenAt = 0; tokenAt < data.at(dataAt)->templates.at(templatesAt)->tokens.size(); tokenAt++)
                {
                    unsigned int wordsAt;

                    for(wordsAt = 0; wordsAt < data.at(dataAt)->words.size(); wordsAt++)
                    {
                        if(data.at(dataAt)->templates.at(templatesAt)->tokens.at(tokenAt) == data.at(dataAt)->words.at(wordsAt)->word)
                        {
                            break;
                        }
                    }
                    if(wordsAt >= data.at(dataAt)->words.size() )
                    {
                        data.at(dataAt)->words.push_back(new Word(data.at(dataAt)->templates.at(templatesAt)->tokens.at(tokenAt) ) );
                    }
                }
            }
            templates = false;
        }
        else if(reading.at(readingAt) == "*")
        {
            dataAt++;
            templates = true;
        }
        else if(templates)
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
                data.push_back(new Data(input.at(readingAt), line) );
            }
            else
            {
                data.at(dataAt)->templates.push_back(new Templates(input.at(readingAt), line) );
            }
        }
        else
        {
            data.at(dataAt)->response.push_back(input.at(readingAt) );
        }
    }
}

AI::~AI()
{
    for(unsigned int i = 0; i < data.size(); i++)
    {
        delete data.at(i);
    }
}

void AI::input()
{
    srand(time(NULL) );

    std::string text;

    std::cout << "[CHAT AI]" << std::endl << "> ";
    while(getline(std::cin, text) )
    {
        if(text == "/exit")
        {
            break;
        }
        if(text == "/chat")
        {
            if(data.size() == 0)
            {
                std::cout << "[CHAT AI] >>> [EMPTY DATABASE]" << std::endl;
            }
            else
            {
                unsigned int index = rand() % data.size();

                std::cout << "[CHAT AI] >>> " << data.at(index)->templates.at(rand() % data.at(index)->templates.size() )->line << std::endl << ">: ";
                getline(std::cin, text);
                if(text.size() == 0 || text.at(0) == '/')
                {
                    std::cout << "[CHAT AI] >>> [RESPONSE DISCARDED]";
                }
                else
                {
                    unsigned int i;

                    for(i = 0; i < data.at(index)->response.size(); i++)
                    {
                        if(text == data.at(index)->response.at(i) )
                        {
                            break;
                        }
                    }
                    if(i >= data.at(index)->response.size() )
                    {
                        data.at(index)->response.push_back(text);
                    }
                    std::cout << "[CHAT AI] >>> [RESPONSE RECORDED]";
                }
                std::cout << std::endl;
            }
        }
        else if(text.size() == 0 || text.at(0) == '/')
        {
            std::cout << "[CHAT AI] >>> [INVALID INPUT]" << std::endl;
        }
        else
        {
            std::string parse = text;
            for(int i = 0; i < int(parse.size() ); i++)
            {
                if( (parse.at(i) < 'A' && parse.at(i) != ' ') || (parse.at(i) > 'Z' && parse.at(i) < 'a') || parse.at(i) > 'z')
                {
                    parse.erase(i, 1);
                    i--;
                }
                else if(parse.at(i) >= 'A' && parse.at(i) <= 'Z')
                {
                    parse.at(i) = int(parse.at(i) ) + 32;
                }
            }

            std::size_t found;
            int index = 0;
            std::vector<std::string> input;

            while( (found = parse.find(' ', index) ) != std::string::npos)
            {
                input.push_back(parse.substr(index, found - index) );
                index = found + 1;
            }
            if(index < int(parse.size() ) )
            {
                input.push_back(parse.substr(index, parse.size() - index) );
            }

            double tolerance = 0.90;
            double max = 0.0;
            double check = 0.0;

            index = -1;
            for(unsigned int dataAt = 0; dataAt < data.size(); dataAt++)
            {
                for(unsigned int templatesAt = 0; templatesAt < data.at(dataAt)->templates.size(); templatesAt++)
                {
                    unsigned int count = 0;

                    for(unsigned int inputAt = 0; inputAt < input.size(); inputAt++)
                    {
                        for(unsigned int tokenAt = 0; tokenAt < data.at(dataAt)->templates.at(templatesAt)->tokens.size(); tokenAt++)
                        {
                            if(input.at(inputAt) == data.at(dataAt)->templates.at(templatesAt)->tokens.at(tokenAt) )
                            {
                                count++;

                                break;
                            }
                        }
                    }

                    double value;
                    if(double(count) / double(data.at(dataAt)->templates.at(templatesAt)->tokens.size() ) < double(data.at(dataAt)->templates.at(templatesAt)->tokens.size() ) / double(count) )
                    {
                        value = double(count) / double(data.at(dataAt)->templates.at(templatesAt)->tokens.size() );
                    }
                    else
                    {
                        value = double(data.at(dataAt)->templates.at(templatesAt)->tokens.size() ) / double(count);
                    }
                    double checks = value;

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
                        check = checks;
                    }
                }
            }
            if(index > -1 && check < 1.0)
            {
                data.at(index)->templates.push_back(new Templates(text, input) );
                for(unsigned int wordsAt = 0; wordsAt < data.at(index)->words.size(); wordsAt++)
                {
                    for(unsigned int inputAt = 0; inputAt < input.size(); inputAt++)
                    {
                        if(data.at(index)->words.at(wordsAt)->word == input.at(inputAt) )
                        {
                            data.at(index)->words.at(wordsAt)->count++;

                            break;
                        }
                    }
                }
                for(unsigned int inputAt = 0; inputAt < input.size(); inputAt++)
                {
                    unsigned int wordsAt;

                    for(wordsAt = 0; wordsAt < data.at(index)->words.size(); wordsAt++)
                    {
                        if(input.at(inputAt) == data.at(index)->words.at(wordsAt)->word )
                        {
                            break;
                        }
                    }
                    if(wordsAt >= data.at(index)->words.size() )
                    {
                        data.at(index)->words.push_back(new Word(input.at(inputAt) ) );
                    }
                }
                for(int templatesAt = 0; templatesAt < int(data.at(index)->templates.size() ); templatesAt++)
                {
                    check = tolerance;
                    for(unsigned int wordsAt = 0; wordsAt < data.at(index)->words.size(); wordsAt++)
                    {
                        unsigned int tokenAt;

                        for(tokenAt = 0; tokenAt < data.at(index)->templates.at(templatesAt)->tokens.size(); tokenAt++)
                        {
                            if(data.at(index)->words.at(wordsAt)->word == data.at(index)->templates.at(templatesAt)->tokens.at(tokenAt) )
                            {
                                check += 0.01 * data.at(index)->words.at(wordsAt)->count;

                                break;
                            }
                        }
                        if(tokenAt >= data.at(index)->templates.at(templatesAt)->tokens.size() )
                        {
                            check -= 0.01 * data.at(index)->words.at(wordsAt)->count;
                        }
                    }
                    if(check < tolerance)
                    {
                        for(int wordsAt = 0; wordsAt < int(data.at(index)->words.size() ); wordsAt++)
                        {
                            unsigned int tokenAt;

                            for(tokenAt = 0; tokenAt < data.at(index)->templates.at(templatesAt)->tokens.size(); tokenAt++)
                            {
                                if(data.at(index)->words.at(wordsAt)->word == data.at(index)->templates.at(templatesAt)->tokens.at(tokenAt) )
                                {
                                    data.at(index)->words.at(wordsAt)->count--;
                                    if(data.at(index)->words.at(wordsAt)->count == 0)
                                    {
                                        data.at(index)->words.erase(data.at(index)->words.begin() + wordsAt);
                                        wordsAt--;
                                    }

                                    break;
                                }
                            }
                        }
                        data.at(index)->templates.erase(data.at(index)->templates.begin() + templatesAt);
                        templatesAt--;
                    }
                }
            }
            else if(index <= -1)
            {
                data.push_back(new Data(text, input) );
                index = data.size() - 1;
                for(unsigned int i = 0; i < input.size(); i++)
                {
                    data.at(index)->words.push_back(new Word(input.at(i) ) );
                }
            }
            if(data.at(index)->response.size() > 0)
            {
                std::cout << "[CHAT AI] >>> " << data.at(index)->response.at(rand() % data.at(index)->response.size() ) << std::endl;
            }
            else
            {
                std::cout << "[CHAT AI] >>> [INPUT RESPONSE]" << std::endl << ">: ";
                getline(std::cin, text);
                if(text.size() == 0 || text.at(0) == '/')
                {
                    std::cout << "[CHAT AI] >>> [RESPONSE DISCARDED]" << std::endl;
                }
                else
                {
                    data.at(index)->response.push_back(text);
                    std::cout << "[CHAT AI] >>> [RESPONSE RECORDED] " << data.at(index)->response.at(0) << std::endl;
                }
            }
        }
        std::cout << "> ";
    }

    return;
}

std::string AI::save(bool templates, int & data, int & value)
{
    int at = data;
    int index = value;

    value++;
    if(this->data.size() == 0)
    {
        data = -1;
        value = -2;

        return "";
    }
    if(templates)
    {
        if(value >= int(this->data.at(at)->templates.size() ) )
        {
            value = -1;
        }

        return this->data.at(at)->templates.at(index)->line;
    }
    if(this->data.at(at)->response.size() == 0 || value >= int(this->data.at(at)->response.size() ) )
    {
        data++;
        if(data >= int(this->data.size() ) )
        {
            data = -1;
        }
        if(this->data.at(at)->response.size() == 0)
        {
            value = -2;

            return "";
        }
        value = -1;
    }

    return this->data.at(at)->response.at(index);
}

Data::Data(std::string line, std::vector<std::string> & tokens)
{
    this->templates.push_back(new Templates(line, tokens) );
}

Data::~Data()
{
    for(unsigned int i = 0; i < words.size(); i++)
    {
        delete words.at(i);
    }
    for(unsigned int i = 0; i < templates.size(); i++)
    {
        delete templates.at(i);
    }
}

Templates::Templates(std::string line, std::vector<std::string> & tokens)
{
    this->line = line;
    this->tokens = tokens;
}

Word::Word(std::string word)
{
    this->word = word;
    count = 1;
}