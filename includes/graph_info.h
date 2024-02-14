#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <list>
#include <cassert>
#include <string>
#include <SFML/Graphics.hpp>
#include "domain.h"
#include "constants.h"

using namespace std;

struct graph_info
{
public:
    graph_info():_equation(" "), _origin(sf::Vector2f(WORK_PANEL/2, SCREEN_HEIGHT/2)), _d(-2, 2), y_axis(-2, 2),
    _window_dimensions(sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT))
    {
        cout<<"graph_info CTOR Fired.\n";
    }
    string _equation;
    vector<sf::Vector2f> _points;
    sf::Vector2f _origin;
    Domain _d;
    Domain y_axis;
    sf::Vector2f _window_dimensions;
    int amount_of_points;
    friend ostream& operator << (ostream& outs, const graph_info& other)
    {
        outs<<"Eq: " <<other._equation<<"\n";
        outs<<"_points: ";
        for(int i = 0; i < other._points.size(); i++)
        {
            outs <<"<"<<other._points[i].x<<", "<<other._points[i].y<<"> ,";
        }
        outs<<"\n";
        outs<<"_origin: <"<<other._origin.x<<","<<other._origin.y<<">\n";
        outs<<other._d<<"\n";
        outs<<"amount_of_points: "<<other.amount_of_points<<"\n";
        return outs;
    } 
};

#endif