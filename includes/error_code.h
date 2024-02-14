#ifndef ERROR_CODE_H
#define ERROR_CODE_H

#include <iostream>
#include <iomanip>

using namespace std;

struct Error_Code
{
public:
    int _code;
    Error_Code(): _code(0) {}
    string get_error_string()
    {
        string error_string;
        switch (_code)
        {
        case 1:
            error_string = "Division by Zero Error. Please try again.";
            break;
        case 2:
            error_string = "Missing Left Parenthesis. Please try again.";
            break;
        case 3:
            error_string = "Missing Right Parenthesis. Please try again.";
            break;
        default:
            error_string = "Wrong Error Code";
            break;
        }
        return error_string;
    }
    friend ostream& operator << (ostream& outs, const Error_Code& other)
    {
        // outs<<"hi error_code\n";
        outs<<"error_code: [ "<<other._code<<" ]";
        return outs;
    }  
};


#endif