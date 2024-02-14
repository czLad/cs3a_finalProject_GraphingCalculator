#ifndef FUNCTION_H
#define FUNCTION_H

#include "operator.h"

using namespace std;

class Function : public Operator
{
public:
    Function()
    {
        //Functions have the highest precedence
        set_precedence(8);
        _func = " ";
    }
    Function(const string& func) : Operator(func)
    {
        set_precedence(8);
        _func = func;
        //op_type 2: treats function as Integer in RPN
        //op_type 3: treats function as Single Argument Operators in RPN
        if(_func.size() == 1)
        {
            //"&" for unary minus
            if(_func == "&")
            {
                set_precedence(2);
                set_op_type(3);
            }
            else
                set_op_type(2);

        }     
        if(_func.size() > 1)
            set_op_type(3);   
    }
private:
    string _func;
};

#endif