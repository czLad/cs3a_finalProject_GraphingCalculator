#include "system.h"
#include "constants.h"
#include <iostream>

using namespace std;

System::System()
{
    //^Prof's code
    
    //Prof's code
    // shape.setPosition(sf::Vector2f(xpos, ypos));
    // vel = sf::Vector2f(r.Next(-5, 5), r.Next(5 , 5)); //(-5, 5); //(r.Next(-5, 0), r.Next(0 , 5)); // random velocity
    // int r_ = r.Next(0, 255);
    // int g_ = r.Next(0, 255);
    // int b_ = r.Next(0, 255);
    // shape.setFillColor(sf::Color(r_, g_, b_));
}

//------------------------------------------------------------------
//------------------------------------------------------------------

// void System::Step(int command)
// {
    
//     //Prof's code
//     // sf::Vector2f pos = shape.getPosition();
//     // if ((pos.x) >= WORK_PANEL - 20)
//     //     vel = sf::Vector2f(-1 * vel.x, 1 * vel.y);
//     // if (pos.x <= 0)
//     //     vel = sf::Vector2f(-1 * vel.x, 1 * vel.y);
//     // if ((pos.y) >= SCREEN_HEIGHT - 20)
//     //     vel = sf::Vector2f(1 * vel.x, -1 * vel.y);
//     // if (pos.y <= 0)
//     //     vel = sf::Vector2f(1 * vel.x, -1 * vel.y);
// }

void System::Draw(sf::RenderWindow &window)
{
    //Graph update
    //Graph draw
    _g.update();
    _g.Draw(window);
}
//^ Version 1 used this
// void System::Draw(sf::RenderWindow &window)
// {
//     //Graph draw
//     _g.Draw(window);
// }
//^ Version 2 uses this but too much pressure on cpu