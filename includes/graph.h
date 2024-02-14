#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "graph_info.h"
#include "constants.h"
#include "plot.h"

using namespace std;

const float AXIS_THICKNESS = 3;

class Graph
{
public:
    Graph(){}
    Graph(graph_info* info): _info(info)
    {
        const bool debug = false;
        if(debug)
            cout << "Graph(graph_info* info) CTOR Fired.\n";
        _plotter = Plot(_info);
    }
    void set_info(){}
    void Draw(sf::RenderWindow& window) //Draws axis and points
    {
        sf::RectangleShape x_axis;
        x_axis.setSize(sf::Vector2f(WORK_PANEL, AXIS_THICKNESS));
        x_axis.setPosition(0, _info->_origin.y - AXIS_THICKNESS / 2);
        x_axis.setFillColor(sf::Color::White);

        sf::RectangleShape y_axis;
        y_axis.setSize(sf::Vector2f(AXIS_THICKNESS, SCREEN_HEIGHT));
        y_axis.setPosition(_info->_origin.x - AXIS_THICKNESS / 2, 0);
        y_axis.setFillColor(sf::Color::White);
        window.draw(x_axis);
        window.draw(y_axis);
        // cout<<"hi X_Y axis drawn.\n";
        // cout << _info->_d << "\n";

        // cout <<"_info->_points.size(): " << _info->_points.size()<<"\n";
        //Draws the graph using _points vector
        for(int i = 0; i < _info->_points.size(); i++)
        {
            sf::CircleShape point;
            point.setRadius(1.0);
            point.setFillColor(sf::Color::Red);
            point.setPosition(_info->_points[i]);
            // cout<<"<"<<_info->_points[i].x <<"|"<< _info->_points[i].y <<">\n";
            point.setOrigin(1, 1);
            window.draw(point);
        }
    }
    // v Version 2 trying plotting without having a vector of vector2fs
    // void Draw(sf::RenderWindow& window) //Draws axis and points
    // {
    //     const bool debug = false;
    //     if(debug)
    //         cout << "Plot set_info() Fired.\n";
        
    //     Tokenizer t;
    //     //Calculating one screen unit using window dimensions and domains
    //     double one_screen_unit = _info->_window_dimensions.x / (_info->_d._upper_bound - _info->_d._lower_bound);
    //     //_info->origin.x is used to set the position of the Y-axis
    //     //_info->origin.y is used to set the position of the X-axis
    //     _info->_origin.x = one_screen_unit * -(_info->_d._lower_bound);
    //     _info->_origin.y = one_screen_unit * _info->y_axis._upper_bound;
    //     // Drawing X Y - axis
    //     sf::RectangleShape x_axis;
    //     x_axis.setSize(sf::Vector2f(WORK_PANEL, AXIS_THICKNESS));
    //     x_axis.setPosition(0, _info->_origin.y - AXIS_THICKNESS / 2);
    //     x_axis.setFillColor(sf::Color::White);

    //     sf::RectangleShape y_axis;
    //     y_axis.setSize(sf::Vector2f(AXIS_THICKNESS, SCREEN_HEIGHT));
    //     y_axis.setPosition(_info->_origin.x - AXIS_THICKNESS / 2, 0);
    //     y_axis.setFillColor(sf::Color::White);
    //     window.draw(x_axis);
    //     window.draw(y_axis);
    //     //Tokenizer tokenizes _info->equation to Tokens
    //     //Shuting yard accepts and change it to postfix
    //     ShuntingYard sy(t(_info->_equation));
    //     Queue<Token*>_post_fix = sy.postfix();
    //     if(debug)
    //     {
    //         for(Queue<Token*>::Iterator it = _post_fix.begin(); it != _post_fix.end(); ++it)
    //         {
    //             switch ((*it)->get_integer_type())
    //             {
    //             case 1:
    //                 cout << static_cast<Integer*>(*it)->get_val();
    //             break;
    //             default:
    //                 cout << static_cast<Operator*>(*it)->get_operator();
    //             break;
    //             }
    //         }
    //     }
    //     //v Calculates how much an x-value should be incremented to get from domain lower bound to upper bound
    //     // Using the amount of points wanting to be plotted
    //     float graph_point_inc = (_info->_d._upper_bound - _info->_d._lower_bound) / _info->amount_of_points;
    //     // Check how many points are being plotted
    //     for(float i = _info->_d._lower_bound; i <= _info->_d._upper_bound; i += graph_point_inc)
    //     {
    //         // cout << i << "\n";
    //         //v Local rpn used to evaluate y-values using the x value given by i
    //         RPN rpn(_post_fix);
    //         // Coordinate translator take _info as an argument and push position of each graph point on windows
    //         // into the points vector
    //         Coordinate_translator c1(_info);
    //         //v Draws points
    //         sf::CircleShape point;
    //         point.setRadius(1.0);
    //         point.setFillColor(sf::Color::Red);
    //         point.setPosition(c1.translate(i, rpn(i)));
    //         // cout<<"<"<<_info->_points[i].x <<"|"<< _info->_points[i].y <<">\n";
    //         point.setOrigin(1, 1);
    //         window.draw(point);
    //     }
    // }
    // v Version1 used this to update _info vector
    void update()
    {
        _plotter.set_info();
    }
private:
    Plot _plotter;
    graph_info* _info;
};

#endif