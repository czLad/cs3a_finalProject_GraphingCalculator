#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "graph_info.h"
#include "shunting_yard/shunting_yard.h"
#include "rpn/rpn.h"
#include "token/token.h"
#include "tokenizer.h"
#include "coordinate_translator.h"

using namespace std;

class Plot
{
public:
    Plot(){}
    Plot(graph_info* info):_info(info)
    {
        const bool debug = false;
        if(debug)
            cout << "Plot(graph_info* info) CTOR Fired.\n";
        // set_info();
    }
    void set_info()
    {
        const bool debug = false;
        if(debug)
            cout << "Plot set_info() Fired.\n";
        //clears the points vector
        _info->_points.clear();
        Tokenizer t;
        //Calculating one screen unit using window dimensions and domains
        double one_screen_unit = _info->_window_dimensions.x / (_info->_d._upper_bound - _info->_d._lower_bound);
        //_info->origin.x is used to set the position of the Y-axis
        //_info->origin.y is used to set the position of the X-axis
        _info->_origin.x = one_screen_unit * -(_info->_d._lower_bound);
        _info->_origin.y = one_screen_unit * _info->y_axis._upper_bound;
        //Tokenizer tokenizes _info->equation to Tokens
        //Shuting yard accepts and change it to postfix
        ShuntingYard sy(t(_info->_equation));
        _post_fix = sy.postfix();
        if(debug)
        {
            for(Queue<Token*>::Iterator it = _post_fix.begin(); it != _post_fix.end(); ++it)
            {
                switch ((*it)->get_integer_type())
                {
                case 1:
                    cout << static_cast<Integer*>(*it)->get_val();
                break;
                default:
                    cout << static_cast<Operator*>(*it)->get_operator();
                break;
                }
            }
        }
        //v Calculates how much an x-value should be incremented to get from domain lower bound to upper bound
        // Using the amount of points wanting to be plotted
        float graph_point_inc = (_info->_d._upper_bound - _info->_d._lower_bound) / _info->amount_of_points;
        // Check how many points are being plotted
        for(float i = _info->_d._lower_bound; i <= _info->_d._upper_bound; i += graph_point_inc)
        {
            // cout << i << "\n";
            //v Local rpn used to evaluate y-values using the x value given by i
            RPN rpn(_post_fix);
            // Coordinate translator take _info as an argument and push position of each graph point on windows
            // into the points vector
            Coordinate_translator c1(_info);
            // i is the graph x value rpn(i) is the graph y value
            _info->_points.push_back(c1.translate(i, rpn(i)));
        }
    }
private:
    Queue<Token*> _post_fix;
    graph_info* _info;
};

#endif