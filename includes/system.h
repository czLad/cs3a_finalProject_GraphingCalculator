#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "graph_info.h"
#include "graph.h"

using namespace std;
class System
{
public:
    System();
    System(graph_info* info): _info(info) {
        _g = Graph(_info);
    }
    void set_info(graph_info* info) 
    {
        //default set_info
        _info = info;
        _info->_d._lower_bound = -2;
        _info->_d._upper_bound = 2;
    }
    void Step(int command)
    {
        int step_to_border = 50;
        double domain_total;
        double one_step;
        double symmetric_domain;
        switch (command)
        {
        //pan left
        case 4:
            domain_total = _info->_d._upper_bound - _info->_d._lower_bound;
            one_step = domain_total / step_to_border;
            _info->_d._lower_bound += one_step;
            _info->_d._upper_bound += one_step;
            break;
        //pan right
        case 6:
            domain_total = _info->_d._upper_bound - _info->_d._lower_bound;
            one_step = domain_total / step_to_border;
            _info->_d._lower_bound -= one_step;
            _info->_d._upper_bound -= one_step;
            break;
        //pan up
        case 14:
            domain_total = _info->y_axis._upper_bound - _info->y_axis._lower_bound;
            one_step = domain_total / step_to_border;
            _info->y_axis._lower_bound += one_step;
            _info->y_axis._upper_bound += one_step;
            break;
        //pan down
        case 16:
            domain_total = _info->y_axis._upper_bound - _info->y_axis._lower_bound;
            one_step = domain_total / step_to_border;
            _info->y_axis._lower_bound -= one_step;
            _info->y_axis._upper_bound -= one_step;
            break;
        //zoom out
        case 3:
            _info->_d._lower_bound *= 0.70;
            _info->_d._upper_bound *= 0.70;
            _info->y_axis._lower_bound *= 0.70;
            _info->y_axis._upper_bound *= 0.70;
            break;
        //zoom in
        case 5:
            _info->_d._lower_bound *= 1.20;
            _info->_d._upper_bound *= 1.20;
            _info->y_axis._lower_bound *= 1.20;
            _info->y_axis._upper_bound *= 1.20;
            break;
        //Origin
        case 8:
            _info->_d._upper_bound = 5;
            _info->_d._lower_bound = -5;
            _info->y_axis._upper_bound = 5;
            _info->y_axis._lower_bound = -5;
            break;
        default:
            break;
        }
    }
    int Size();
    void Draw(sf::RenderWindow& widnow);
private:
    int particles;
    graph_info* _info;
    Graph _g;
};

#endif // SYSTEM_H
