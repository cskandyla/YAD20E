#include "ScriptHandler.h"
#include <iostream>
#include "Tokenizer.h"
#include "Game.h"
using std::cout;
using std::endl;


void Defaulthandler(const char *s,Game *g)
{
    Tokenizer tok;
    tok.setDelimeter(" ");
    tok.setInput(s);
    vector<string> vecs=tok.split();
    /*for(int i=0;i<vecs.size();i++)
    {
        cout<<vecs[i]<<endl;
    }*/
    if(vecs.size()>0)
    {
        if(vecs.at(0).compare("Print")==0)
        {
            for(int i=1; i<vecs.size(); i++)
                cout<<vecs[i]<<" ";
            cout<<endl;
        }
        else if(vecs.at(0).compare("Write")==0)
        {
            cout<<"Writting:"<<endl;
        }
        else if(vecs.at(0).compare("Exit")==0 || vecs.at(0).compare("exit")==0)
        {
            cout<<"Exiting..."<<endl;
        }
        else if(vecs.at(0).compare("Echo")==0)
        {
            g->Log->AddText(vecs.at(1),220,220,0);
        }



    }


}

ScriptHandler::ScriptHandler(void (*handlerfuntion)(const char *s,Game *ga),Game *ga)
{
    this->handlerfuntion=handlerfuntion;
    this->game=ga;
}

void ScriptHandler::CallHandler(const char *s)
{


    handlerfuntion(s,game);
}
