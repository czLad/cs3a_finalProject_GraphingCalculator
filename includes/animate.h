#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "system.h"
#include "sidebar.h"
#include "graph_info.h"
#include "textbox.h"

using namespace std;

class animate{
public:
    animate();
    void run();
    void processEvents();
    void update();
    void render();
    void Draw();
    ~animate()
    {
        delete _info;
        delete _sidebar;
    }
private:
    graph_info* _info;
    sf::RenderWindow window;
    sf::CircleShape mousePoint;         //The little red dot
    System system;                      //container for all the animated objects
    int command;                        //command to send to system
    sf::Font font;                      //font to draw on main screen
    sf::Text myTextLabel;               //text to draw on main screen
    sf::Text error_text;
    bool display_error;
    bool mouseIn;                       //mouse is in the screen
    // Sidebar sidebar;                    //rectangular message sidebar
    bool textbox_opened;
    Textbox textbox;
    bool first_text_input;
    Sidebar* _sidebar;                  //rectangular message sidebar_ptr
};

string mouse_pos_string(sf::RenderWindow& window);

#endif // GAME_H
