#include "Tokenizer.h"


Tokenizer::Tokenizer(): input(""), token(""), delimiters(" \t\v\n\r")
{


    this->pos = input.begin();
    this->numtokens=0;

}


Tokenizer::Tokenizer(const std::string& str, const std::string& delimiter) : input(str), token(""), delimiters(delimiters)
{
    pos = input.begin();
}


Tokenizer::~Tokenizer()
{

}

void Tokenizer::setInput(const string& input)
{
    this->input=input;
    this->pos=this->input.begin();
    this->numtokens=0;
}


void Tokenizer::setDelimeter(const string& delimiters)
{
    this->delimiters=delimiters;
    this->pos=input.begin();
}


bool Tokenizer::isdelim(char c)
{
    return (delimiters.find(c) != std::string::npos);
}


void Tokenizer::skipdelim()
{
    while(pos != input.end() && isdelim(*pos))
        ++pos;
}


string Tokenizer::getnext()
{
    if(input.size() <= 0) return "";

    token.clear();

    this->skipdelim();


    while(pos != input.end() && !isdelim(*pos))
    {
        if(isprint(*pos))
            token += *pos;
        ++pos;
    }
    numtokens++;
    return token;
}

vector<string> Tokenizer::split()
{
    vector<string> tokens;
    string token;
    while((token = this->getnext()) != "")
    {
        tokens.push_back(token);
    }

    return tokens;
}


void Tokenizer::clear()
{
    this->input="";
    setDelimeter(" \r\n");

}



