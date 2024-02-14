#ifndef INTEGER_H
#define INTEGER_H

#include "token.h"
#include "string"

using namespace std;

class Integer : public Token
{
public:
    Integer()
    {
        set_integer_type(1);
        _val = 0;
    }
    Integer(double val) : Token()
    {
        set_integer_type(1);
        _val = val;
    }
    Integer(const string& val) : Token()
    {
        set_integer_type(1);
        _val = stod(val);
    }
    double get_val()
    {
        return _val;
    }

    
private:
    double _val;
};


#endif