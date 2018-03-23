#include <string>
#include <vector>
using namespace std;


#ifndef __TOKENIZER__
#define __TOKENIZER__
class Tokenizer
{
private:
    string delimiters;
    string input;
    string token;
    string::const_iterator pos;
    int numtokens;
    bool isdelim(char c);
    void skipdelim();

public:
    Tokenizer();
    Tokenizer(const string& input,const string& delimeters=" \n\r");
    ~Tokenizer();
    void setDelimeter(const string& delimeters);
    void setInput(const string& input);
    string getnext();
    vector<string> split();
    int getnumtokens()
    {
        return numtokens;
    }
    void clear();

};
#endif
