#ifndef RPN_H
#define RPN_H

// #include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/integer.h"
#include "../token/leftparen.h"
#include "../token/operator.h"
#include "../token/rightparen.h"
#include "../token/function.h"

using namespace std;

class RPN
{
public:
    RPN(){;}
    RPN(const Queue<Token*> &postfix) : _postfix(postfix){;}
    double operator()(const double& x_value = 1)
    {
        assert(_postfix.begin() && "Cannot evaluate an empty queue");
        const bool debug = false;
        Stack<Token*> rpn_stack;
        for(Queue<Token*>::Iterator it = _postfix.begin(); it != _postfix.end(); ++it)
        {
            double first_pop;
            double second_pop;
            double result;
            if(debug)
                cout <<"switch: "<<(*it)->get_integer_type()<< "\n";
            switch((*it)->get_integer_type())
            {
                // If number just push it into stack
                case 1:
                if(debug)
                    cout << "case 1 RPN\n";
                rpn_stack.push(*it);
                break;
                // If an operator push the stack once or twice depending on the operator
                // evaluate and push it back in
                case 2:
                if(debug)
                    cout << "case 2 RPN\n";
                switch(static_cast<Operator*>(*it)->get_op_type())
                {
                    // case 1 for operators + - * / ^ 
                    case 1:
                    if(debug)
                        cout << "case 2-1 RPN\n";
                    first_pop = static_cast<Integer*>(rpn_stack.pop())->get_val();
                    second_pop = static_cast<Integer*>(rpn_stack.pop())->get_val();
                    result = static_cast<Operator*>(*it)->evaluate(second_pop, first_pop);
                    rpn_stack.push(new Integer(result));
                    break;
                    //case 2 is for variables e.g. "X"
                    case 2:
                    if(debug)
                        cout << "case 2-2 RPN\n";
                    rpn_stack.push(new Integer(x_value));
                    break;
                    //case 3 is for trig and log funcs e.g.sin
                    case 3:
                    if(debug)
                        cout << "case 2-3 RPN\n";
                    first_pop = static_cast<Integer*>(rpn_stack.pop())->get_val();
                    result = static_cast<Operator*>(*it)->evaluate(first_pop);
                    rpn_stack.push(new Integer(result));
                    break;
                }
                break;
            }
        }
        if(debug)
        {
            Stack<Token*>::Iterator it_debug= rpn_stack.begin();
            cout << "Last element in stack: "<< static_cast<Integer*>(*it_debug)->get_val()<<"\n";
            cout << "RPN loop end\n";
        }
    
        return static_cast<Integer*>(rpn_stack.pop())->get_val();
    }
    friend ostream& operator << (ostream& outs, const RPN& print_me)
    {
        outs<< print_me._postfix;
        return outs;
    }
    void set_input(const Queue<Token*> &postfix)
    {
        _postfix = postfix;
    }

private:
    Queue<Token*> _postfix;
};



#endif