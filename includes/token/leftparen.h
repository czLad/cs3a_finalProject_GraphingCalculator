#ifndef LEFTPAREN_H
#define LEFTPAREN_H

#include "token.h"

using namespace std;

class LeftParen : public Token
{
public:
    LeftParen()
    {
        set_integer_type(3);
        _stub = 0;
    }
private:
    int _stub;
};


#endif