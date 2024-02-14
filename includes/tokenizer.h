#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <iomanip>
#include <vector>
#include "queue/MyQueue.h"
#include "token/token.h"
#include "string.h"
#include "token/integer.h"
#include "token/leftparen.h"
#include "token/operator.h"
#include "token/rightparen.h"
#include "token/function.h"
#include "math.h"

using namespace std;

class Tokenizer
{
public:
    Tokenizer()
    {
        const bool debug = false;
        if(debug)
        {
            cout << "Tokenizer CTOR() Fired.\n";
        }
        _equation = "";
    }
    //Returns a tokenized queue of the equation string
    Queue<Token*> operator() (const string& equation)
    {
        const bool debug = false;
        if(debug)
            cout << "Tokenizer operator() Fired.\n";
        // cout <<"equation from argument: "<<equation << "\n";
        Queue<Token*>infix_queue;
        string _equation = equation;
        //Space added to end of equation for tokenizer to detect _eq end and
        //push appropriately into queue
        _equation += " ";
        if(debug)
            cout <<"_equation: "<<_equation<<"<-\n";
        string ch_string = "";
        bool was_alpha = false;
        bool was_digit_or_dot = false;
        bool was_other = false;
        bool was_right_paren = false;
        bool was_unary_minus = false;
        //Keeps track of last thing pushed to differentiate between minus and unary minus
        bool pushed_x_or_e = false;

        //Cannot allow 
        //"For double negatition or above put paraenthesis -(-5)"
        //"For unary minus behind operators put parenthesis 3*(-5)"
        //Detecting type changes in for loop
        
        for(int i = 0; i < _equation.size(); i++)
        {
            // Checks for unary minus if last char in the loop was unary minus
            // If so sets unary minus to true
            if(_equation[i] == '-' && !was_digit_or_dot && !was_right_paren)
            {
                // If was_alpha boolean was true push token into infix_queue
                if(was_alpha)
                {
                    if(ch_string.size() == 1 && ch_string == "e")
                    {
                        infix_queue.push(new Integer(M_E));
                        pushed_x_or_e = true;
                    }
                    else
                    {
                        infix_queue.push(new Function(ch_string));
                        if(ch_string.size() == 1)
                            pushed_x_or_e = true;
                    }
                        // infix_queue.push(new Function(ch_string));
                    was_alpha = false;
                    ch_string = "";
                }
                // If was_other boolean was true push token into infix_queue
                if(was_other)
                {
                    if(ch_string.size() == 1 && ch_string == "(")
                    {
                        infix_queue.push(new LeftParen());
                    }
                    else
                    {
                        infix_queue.push(new Operator(ch_string));
                    }
                    was_other = false;
                    ch_string = "";
                }
                // If one of the statements pushed the token x as a variable or
                // pushed the integer e sets unary minus to false
                // else sets was_unary_minus boolean to true
                if(pushed_x_or_e)
                {
                    was_unary_minus = false;
                    was_other = true;
                    pushed_x_or_e = false;
                }
                else
                    was_unary_minus = true;
            }
            // If its a digit or the decimal point sets was_digit_or_dot boolean to true
            else if(isdigit(_equation[i]) || _equation[i] == '.')
            {
                if(was_alpha)
                {
                    if(ch_string.size() == 1 && ch_string == "e")
                    {
                        infix_queue.push(new Integer(M_E));
                    }
                    else
                        infix_queue.push(new Function(ch_string));
                    was_alpha = false;
                    ch_string = "";
                }
                if(was_other)
                {
                    if(ch_string.size() == 1 && ch_string == "(")
                    {
                        infix_queue.push(new LeftParen());
                    }
                    else if (ch_string.size() == 1 && ch_string == ")")
                    {
                        was_right_paren = false;
                        infix_queue.push(new RightParen());
                    }
                    else
                    {
                        infix_queue.push(new Operator(ch_string));
                    }
                    was_other = false;
                    ch_string = "";
                }
                if(was_unary_minus)
                {
                    infix_queue.push(new Function("&"));
                    was_unary_minus = false;
                    ch_string = "";
                }
                was_digit_or_dot = true;
            }
            // If char is alpha sets was_alpha boolean to true
            else if(isalpha(_equation[i]))
            {
                if(was_digit_or_dot)
                {
                    infix_queue.push(new Integer(ch_string));
                    was_digit_or_dot = false;
                    ch_string = "";
                }
                if(was_other)
                {
                    if(ch_string.size() == 1 && ch_string == "(")
                    {
                        infix_queue.push(new LeftParen());
                    }
                    else if (ch_string.size() == 1 && ch_string == ")")
                    {
                        was_right_paren = false;
                        infix_queue.push(new RightParen());
                    }
                    else
                    {
                        infix_queue.push(new Operator(ch_string));
                    }
                    was_other = false;
                    ch_string = "";
                }
                if(was_unary_minus)
                {
                    infix_queue.push(new Function("&"));
                    was_unary_minus = false;
                    ch_string = "";
                }
                was_alpha = true;
            }
            //checking what's at the end of eq to know what the last one was
            //and push as respective token
            else if(_equation[i] == ' ')
            {
                if(was_alpha)
                {
                    if(ch_string.size() == 1 && ch_string == "e")
                    {
                        infix_queue.push(new Integer(M_E));
                    }
                    else
                        infix_queue.push(new Function(ch_string));
                    was_alpha = false;
                    ch_string = "";
                }
                if(was_digit_or_dot)
                {
                    infix_queue.push(new Integer(ch_string));
                    was_digit_or_dot = false;
                    ch_string = "";
                }
                if(was_other)
                {
                    if(ch_string.size() == 1 && ch_string == "(")
                    {
                        infix_queue.push(new LeftParen());
                    }
                    else if (ch_string.size() == 1 & ch_string == ")")
                    {
                        was_right_paren = false;
                        infix_queue.push(new RightParen());
                    }
                    else
                    {
                        infix_queue.push(new Operator(ch_string));
                    }
                    was_other = false;
                    ch_string = "";
                }
                if(was_unary_minus)
                {
                    infix_queue.push(new Function("&"));
                    was_unary_minus = false;
                    ch_string = "";
                }
            }
            else
            {
                if(was_other)
                {
                   if(ch_string.size() == 1 && ch_string == "(")
                    {
                        infix_queue.push(new LeftParen());
                    }
                    else if (ch_string.size() == 1 & ch_string == ")")
                    {
                        was_right_paren = false;
                        infix_queue.push(new RightParen());
                    }
                    else
                    {
                        infix_queue.push(new Operator(ch_string));
                    }
                    was_other = false;
                    ch_string = ""; 
                }
                if(was_alpha)
                {
                    if(ch_string.size() == 1 && ch_string == "e")
                    {
                        infix_queue.push(new Integer(M_E));
                    }
                    else
                        infix_queue.push(new Function(ch_string));
                    was_alpha = false;
                    ch_string = "";
                }
                if(was_digit_or_dot)
                {
                    infix_queue.push(new Integer(ch_string));
                    was_digit_or_dot = false;
                    ch_string = "";
                }
                if(was_unary_minus)
                {
                    infix_queue.push(new Function("&"));
                    was_unary_minus = false;
                    ch_string = "";
                }
                if(_equation[i] == ')')
                    was_right_paren = true;

                was_other = true;
            }
            ch_string += _equation[i];
        }
        if(debug)
        {
            cout << infix_queue << "\n";
            cout << "infix_queue: ";
            for(Queue<Token*>::Iterator it = infix_queue.begin(); it != infix_queue.end(); ++it)
            {
                switch ((*it)->get_integer_type())
                {
                case 1:
                    cout << static_cast<Integer*>(*it)->get_val();
                break;
                case 2:
                    if(static_cast<Operator*>(*it)->get_op_type() == 2)
                        cout << "x";
                    else
                        cout << static_cast<Operator*>(*it)->get_operator();
                break;
                case 3:
                    cout << "(";
                break;
                case 4:
                    cout << ")";
                break;
                }
            }
            cout<<"\n"; 
        }
        return infix_queue;
    }
private:
    string _equation;
};

//Backups / Previous Versions

// Queue<Token*> operator() (string equation)
    // {
    //     const bool debug = true;
    //     if(debug)
    //         cout << "Tokenizer operator() Fired.\n";
    //     cout <<"equation from argument: "<<equation << "\n";
    //     Queue<Token*>infix_queue;
    //     string _equation = equation;
    //     // char* _eq_ptr = new char[_equation.size()];
    //     // strcpy(_eq_ptr, _equation.c_str());

    //     for(int i = 0; i < _equation.size(); i++)
    //     {
    //         if(isdigit(_equation[i]))
    //         {
    //             cout <<"_equation[i]: "<<_equation[i]<< "\n";
    //             string temp_equation = "";
    //             temp_equation += _equation[i];
    //             infix_queue.push(new Integer(temp_equation));
    //         }
    //         else if(isalpha(_equation[i]))
    //         {
    //             string temp_equation = "";
    //             temp_equation += _equation[i];
    //             infix_queue.push(new Function(temp_equation));
    //         }
    //         else
    //         {
    //             // cout<<"strlen(token): "<<strlen(token)<<"\n";
    //             // cout<<"token: "<<token<<"\n";
    //             // if(strlen(token) == 1 && token[0] == '(')
    //             if(_equation[i] == '(')
    //             {
    //             // cout << "LeftParen\n";
    //                 infix_queue.push(new LeftParen());
    //             }
    //             // else if (strlen(token) == 1 && token[0] == ')')
    //             else if (_equation[i] == ')')
    //             {
    //             // cout << "RightParen\n";
    //                 infix_queue.push(new RightParen());
    //             }
    //             else
    //             {
    //                 string temp_equation = "";
    //                 temp_equation += _equation[i];
    //                 infix_queue.push(new Operator(temp_equation));
    //             }
    //         }
    //     }
    //     cout << infix_queue << "\n";
    //     cout << "infix_queue: ";
    //     for(Queue<Token*>::Iterator it = infix_queue.begin(); it != infix_queue.end(); ++it)
    //     {
    //         switch ((*it)->get_integer_type())
    //         {
    //         case 1:
    //             cout << static_cast<Integer*>(*it)->get_val();
    //         break;
    //         default:
    //             cout << static_cast<Operator*>(*it)->get_operator();
    //         break;
    //         }
    //     }
    //     cout << "\n";
    //     return infix_queue;
    // }
    // Queue<Token*> operator() (string equation)
    // {
    //     const bool debug = true;
    //     if(debug)
    //         cout << "Tokenizer operator() Fired.\n";
    //     cout <<"equation from argument: "<<equation << "\n";
    //     _equation = equation;
    //     char eq_str[] = " ";
    //     char delim[] = " ";
    //     // char* eq_str;
    //     cout << _equation << "\n";
    //     cout << _equation.c_str() << "\n";
    //     strcpy(eq_str, _equation.c_str());
    //     cout<<"hi\n";
    //     cout <<"eq_str: "<<eq_str <<"\n";
    //     // char* _eq_ptr = _equation.c_str();
    //     char* token = strtok(eq_str, delim);

    //     Queue<Token*>infix_queue;
    //     while(token)
    //     {
    //         cout <<"|"<< token <<"|"<< "\n";
    //         if(isdigit(token[0]))
    //         {
    //             cout << "isdigit(token[0])\n";
    //             cout <<"token: "<<token << "\n";
    //             string token_str = token;
    //             cout <<"token_str |"<< token_str << "|\n";
    //             cout <<"static_cast<int>(token[0]): " <<static_cast<int>(token[0])<<"\n";
    //             cout <<"stod(token_str) "<< stod(token_str)<< "\n";
    //             cout <<"stod(token) "<< stod(token)<< "\n";
    //             infix_queue.push(new Integer(string(token)));
    //             cout << "hi after Integer\n";
    //         }
    //         else if(isalpha(token[0]))
    //         {
    //             if(strlen(token) == 1)
    //             cout << "isalpha(token[0])\n";
    //             infix_queue.push(new Function(token));
    //         }
    //         else
    //         {
    //             cout<<"strlen(token): "<<strlen(token)<<"\n";
    //             cout<<"token: "<<token<<"\n";
    //             if(strlen(token) == 1 && token[0] == '(')
    //             {
    //             // cout << "LeftParen\n";
    //                 infix_queue.push(new LeftParen());
    //             }
    //             else if (strlen(token) == 1 && token[0] == ')')
    //             {
    //             // cout << "RightParen\n";
    //                 infix_queue.push(new RightParen());
    //             }
    //             else
    //                 infix_queue.push(new Operator(token));
    //         }
    //         token = strtok(NULL, delim);  
    //     }
    //     cout <<"Tokenizer infix_queue: "<<infix_queue<<"\n";
    //     return infix_queue;
    // }

#endif