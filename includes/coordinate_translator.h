#ifndef COORDINATE_TRANSLATOR_H
#define COORDINATE_TRANSLATOR_H

#include "graph_info.h"


using namespace std;

class Coordinate_translator
{
public:
    Coordinate_translator(){}
    Coordinate_translator(graph_info* info) : _info(info) {}
    //Returns a vector2f of screen coords
    sf::Vector2f translate(const double& graph_x, const double& graph_y)
    {
        // cout << "translate\n";
        // considering window dimensions are symmetric uses it to convert graph points
        // to screen points
        sf::Vector2f screen_coord;
        double one_screen_unit = _info->_window_dimensions.x / (_info->_d._upper_bound - _info->_d._lower_bound);
        screen_coord.x = _info->_origin.x + graph_x * one_screen_unit;
        screen_coord.y = _info->_origin.y - graph_y * one_screen_unit;
        return screen_coord;
    }
private:
    graph_info* _info;
};

#endif