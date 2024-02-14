#ifndef OPERATOR_H
#define OPERATOR_H

#include "token.h"

using namespace std;

class Operator : public Token
{
public:
    Operator()
    {
        set_integer_type(2);
        _operator = " ";
    }
    Operator(const string &operation) : Token()
    {
        set_integer_type(2);
        set_op_type(1);
        _operator = operation;
        if(_operator == "*")
            _precedence = 3;
        else if(_operator == "/")
            _precedence = 3;
        else if(_operator == "+")
            _precedence = 1;
        else if(_operator == "-")
            _precedence = 1;
        else if(_operator == "^")
            _precedence = 4;
    }
    double evaluate(const double& LHS, const double& RHS)
    {
        bool an_operator = true;
        if(_operator == "*")
            return LHS * RHS;
        else if(_operator == "/")
            return LHS / RHS;
        else if(_operator == "+")
            return LHS + RHS;
        else if(_operator == "-")
            return LHS - RHS;
        else if(_operator == "^")
        {
            return pow(LHS, RHS);
        }

        else
        {
            an_operator = false;
            assert(an_operator == true && "Invalid Operator");
        }
    }
    double evaluate(const double& LHS)
    {
        bool a_function = true;
        if(_operator == "sin")
            return sin(LHS);
        else if(_operator == "cos")
            return cos(LHS);
        else if(_operator == "tan")
            return tan(LHS);
        else if(_operator == "cot")
            return 1/tan(LHS);
        else if(_operator == "sec")
            return 1/cos(LHS);
        else if(_operator == "csc")
            return 1/sin(LHS);
        else if(_operator == "ln")
            return log(LHS);
        else if(_operator == "log" || _operator == "log10")
            return log10(LHS);
        else if(_operator == "sqrt")
            return sqrt(LHS);
        else if(_operator == "asin")
            return asin(LHS);
        else if(_operator == "acos")
            return acos(LHS);
        else if(_operator == "atan")
            return atan(LHS);
        else if(_operator == "asec")
            return acos(1/LHS);
        else if(_operator == "acsc")
            return asin(1/LHS);
        else if(_operator == "acot")
            return atan2(1, LHS);
        else if(_operator == "sinh")
            return sinh(LHS);
        else if(_operator == "cosh")
            return cosh(LHS);
        else if(_operator == "tanh")
            return tanh(LHS);
        else if(_operator == "sech")
            return 1/cosh(LHS);
        else if(_operator == "csch")
            return 1/sinh(LHS);
        else if(_operator == "coth")
            return 1/tanh(LHS);
        else if(_operator == "&")
            return -1 * LHS;
        else
        {
            a_function = false;
            assert(a_function == true && "Invalid Function");
        }        
    }
    int get_precedence(){return _precedence;}
    void set_precedence(const int& precedence){_precedence = precedence;}
    string get_operator(){return _operator;}
    void set_op_type(const int& op_type){_op_type = op_type;}
    int get_op_type(){return _op_type;}

private:
    string _operator;
    int _precedence;
    int _op_type;
};


#endif