#ifndef TOKEN_H
#define TOKEN_H

// #include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

using namespace std;

class Token
{
public:
    Token()
    {
        _integer_type = 0;
    }
    void set_integer_type(int int_type)
    {
        _integer_type = int_type;
    }
    int get_integer_type() {return _integer_type;}
    
private:
    int _integer_type;
}; 

#endif