#ifndef GRAPH_PAYLOAD_H
#define GRAPH_PAYLOAD_H

#include "iostream"
#include "iomanip"
#include "string.h"
#include "domain.h"

using namespace std;


struct graph_payload
{
public:
    graph_payload():_equation(""), _domain(0, 0), _y_axis(0,0), _size(3){}
    graph_payload(const string &equation, const double& domain_lower_bound, const double& domain_upper_bound)
    {
        _equation = equation;
        _domain._lower_bound = domain_lower_bound;
        _domain._upper_bound = domain_upper_bound;
        _size = 3;
    }
    void tokenizer(const string& str) //Payload_structs using Sidebar needs to have tokenizer(str) function 
    {
        string ch_str = "";
        int i;
        if(!str.empty())
        {
            for(i = 0; str[i] != ':'; i++) //Colon needs to be parameterized as type_delimiter later
            {
                ch_str += str[i];
            }
            if(ch_str == "eq")
            {
                ch_str = "";
                for(i += 1; i < str.size(); i++)
                {
                    ch_str += str[i];
                }
                _equation = ch_str;
            }
            else if(ch_str == "d")
            {
                ch_str = "";
                for(i += 1; i < str.size(); i++) //Comma needs to be provided by graph_payload as delimiter for domain
                {
                    if(str[i] == ',')
                    {
                        _domain._lower_bound = stod(ch_str);
                        ch_str = "";
                        i += 1;
                    }
                    ch_str += str[i];
                }
                _domain._upper_bound = stod(ch_str);
            }
            else if(ch_str == "y")
            {
                ch_str = "";
                for(i += 1; i < str.size(); i++) //Comma needs to be provided by graph_payload as delimiter for domain
                {
                    if(str[i] == ',')
                    {
                        _y_axis._lower_bound = stod(ch_str);
                        ch_str = "";
                        i += 1;
                    }
                    ch_str += str[i];
                }
                _y_axis._upper_bound = stod(ch_str);
            }
        }
    }
    friend ostream& operator << (ostream& outs, const graph_payload& other)
    {
        outs<<"Eq: " <<other._equation<<"\n";
        outs<<other._domain;
        return outs;
    }
    bool is_empty()
    {
        if(_equation == "")
            return true;
        else
            return false;
    } 
    string _equation;
    Domain _domain;
    Domain _y_axis;
    int _size;
};


#endif