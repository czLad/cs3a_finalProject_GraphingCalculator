#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H

#include "token.h"

using namespace std;

class RightParen : public Token
{
public:
    RightParen()
    {
        set_integer_type(4);
        _stub = 0;
    }
private:
    int _stub;
};


#endif