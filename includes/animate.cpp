#include "animate.h"
#include "constants.h"
#include <iostream>
#include "system.h"
#include "textbox.h"
#include "graph_payload.h"

using namespace std;

animate::
animate()
{
    _sidebar = new Sidebar(WORK_PANEL, SIDE_BAR, 13);
    cout << "animate CTOR: TOP" << endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML window!");
    // VideoMode class has functions to detect screen size etc.
    // RenderWindow constructor has a third argumnet to set style
    // of the window: resize, fullscreen etc.

    //Initialize graph_info*
    _info = new graph_info();
    _info->_equation = "sin(x^2)";
    _info->amount_of_points = 3000;


    // System will be implemented to manage a vector of objects to be animated.
    //   at that point, the constructor of the System class will take a vector
    //   of objects created by the animate object.
    //   animate will
    system = System(_info);
    window.setFramerateLimit(60);

    mouseIn = true;

    mousePoint = sf::CircleShape();
    mousePoint.setRadius(5.0);
    mousePoint.setFillColor(sf::Color::Red);

    cout << "Geme CTOR. preparing to load the font." << endl;
    //--- FONT ----------
    // font file must be in the "working directory:
    //      debug folder
    // Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    // font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "animate() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }

    //F1 Text
    myTextLabel = sf::Text("Press F1 for user guide", font);
    myTextLabel.setCharacterSize(20);
    myTextLabel.setStyle(sf::Text::Bold);
    myTextLabel.setFillColor(sf::Color::Green);
    myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT - myTextLabel.getLocalBounds().height - 5));

    //Error Text
    error_text = sf::Text("Error Message", font);
    error_text.setCharacterSize(15);
    error_text.setStyle(sf::Text::Bold);
    error_text.setFillColor(sf::Color::Red);
    error_text.setPosition(sf::Vector2f(WORK_PANEL - 340,  myTextLabel.getLocalBounds().height));
    display_error = false;

    //Next update, make user able to set position, texture, scale of textBox
    textbox = Textbox(17, sf::Color::White, false, _info, _sidebar);
    textbox.set_font(font);
    textbox.set_position(sf::Vector2f(50, 29));
    textbox.set_limit(20);
    textbox_opened = false;
    cout << "animate instantiated successfully." << endl;
}

void animate::Draw()
{
    // Look at the data and based on the data, draw shapes on window object.
    system.Draw(window);
    if (mouseIn)
    {
        window.draw(mousePoint);
    }

    _sidebar->draw(window);
    textbox.Draw(window);

    //- - - - - - - - - - - - - - - - - - -
    // getPosition() gives you screen coords, getPosition(window) gives you window coords
    // cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -

    // drawing Test: . . . . . . . . . . . .
    // This is how you draw text:)
    window.draw(myTextLabel);
    if(display_error == true)
        window.draw(error_text);
    //. . . . . . . . . . . . . . . . . . .
}

void animate::update()
{
    // cause changes to the data for the next frame
    system.Step(command);
    command = 0;
    if (mouseIn)
    {
        // mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x - 5,
                               sf::Mouse::getPosition(window).y - 5);

        // mouse location text for sidebar:
        _sidebar->set_utilities(0) = mouse_pos_string(window);
    }
}
void animate::render()
{
    window.clear();
    Draw();
    window.display();
}

void animate::processEvents()
{
    const bool debug = false;
    sf::Event event;
    float mouseX, mouseY;
    while (window.pollEvent(event)) // or waitEvent
    {
        // check the type of the event...
        switch (event.type)
        {
        // window closed
        case sf::Event::Closed:
            window.close();
            break;

        // key pressed

        case sf::Event::KeyPressed:
        if(debug)
            cout << "command: "<<command<<"\n";
        if(!textbox_opened)
        {
            string user_guide_string;
            switch (event.key.code)
            {
            case sf::Keyboard::Left:
                _sidebar->set_utilities(1) = "LEFT ARROW";
                command = 4;
                break;
            case sf::Keyboard::Right:
                _sidebar->set_utilities(1) = "RIGHT ARROW";
                command = 6;
                break;
            case sf::Keyboard::Up:
                _sidebar->set_utilities(1) = "UP ARROW";
                command = 16;
                break;
            case sf::Keyboard::Down:
                _sidebar->set_utilities(1) = "DOWN ARROW";
                command = 14;
                break;
            case sf::Keyboard::O:
                _sidebar->set_utilities(1) = "O";
                command = 8;
                break;
            case sf::Keyboard::Comma:
                _sidebar->set_utilities(1) = "Comma";
                command = 3;
                break;
            case sf::Keyboard::Period:
                _sidebar->set_utilities(1) = "Period";
                command = 5;
                break;
            case sf::Keyboard::B:
                _sidebar->set_utilities(1) = "B";
                textbox_opened = true; //command 11: textbox being called
                textbox.set_selected(true);
                textbox.set_is_key_for_call(true);
                first_text_input = true;
                // textbox.type_on(event);
                break;
            case sf::Keyboard::W:
                _sidebar->set_utilities(1) = "W";
                _sidebar->scroll_up();
                break;
            case sf::Keyboard::S:
                _sidebar->set_utilities(1) = "S";
                _sidebar->scroll_down();
                break;
            case sf::Keyboard::A:
                _sidebar->set_utilities(1) = "A";
                _sidebar->scroll_default();
                break;
            case sf::Keyboard::F1:
                user_guide_string = "Press \nB for Equation input TextBox.\nEnter to close it.\n<- to pan left\n-> to pan right\n^ to pan up\nv to pan down\n";
                user_guide_string += "Period to zoom in\nComma to zoom out\nO for origin\nW to scroll up sidebar\nS to scroll down sidebar\n";
                user_guide_string += "A to scroll default\nF2 to exit UserGuide";
                myTextLabel.setString(user_guide_string.c_str());
                myTextLabel.setCharacterSize(13);
                myTextLabel.setStyle(sf::Text::Italic);
                myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT - myTextLabel.getLocalBounds().height - 5));
                break;
            case sf::Keyboard::F2:
                user_guide_string = "Press F1 for user guide";
                myTextLabel.setString(user_guide_string.c_str());
                myTextLabel.setCharacterSize(20);
                myTextLabel.setStyle(sf::Text::Bold);
                myTextLabel.setFillColor(sf::Color::Green);
                myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT - myTextLabel.getLocalBounds().height - 5));
                break;    
            case sf::Keyboard::Escape:
                _sidebar->set_utilities(1) = "ESC: EXIT";
                window.close();
                break;
            }
        }
            break;
        case sf::Event::TextEntered:
            if(textbox_opened)
            {
                try
                {
                    display_error = false;
                    textbox.type_on(event);
                }
                catch(Error_Code error)
                {
                    display_error = true;
                    error_text.setString(error.get_error_string().c_str());
                }
                textbox.set_is_key_for_call(false);

                if(!textbox.get_is_selected())
                {
                    textbox_opened = false;
                }
            }
            break;

        case sf::Event::MouseEntered:
            mouseIn = true;
            break;

        case sf::Event::MouseLeft:
            mouseIn = false;
            break;

        case sf::Event::MouseMoved:
            mouseX = event.mouseMove.x;
            mouseY = event.mouseMove.y;
            // Do something with it if you need to...
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                // sidebar[SB_MOUSE_CLICKED] = "RIGHT CLICK " +
                //                             mouse_pos_string(window);
            }
            else
            {
                int g_mpos_y = event.mouseButton.y;
                int g_mpos_x = event.mouseButton.x;
                if(_sidebar->get_bounds().contains(g_mpos_x, g_mpos_y))
                {
                    graph_payload g_pyld = _sidebar->atMousePos(g_mpos_x, g_mpos_y);
                    _info->_equation = g_pyld._equation;
                    _info->_d._lower_bound = g_pyld._domain._lower_bound;
                    _info->_d._upper_bound = g_pyld._domain._upper_bound;
                    _info->y_axis._lower_bound = g_pyld._y_axis._lower_bound;
                    _info->y_axis._upper_bound = g_pyld._y_axis._upper_bound;
                }
            }
            break;
        default:
            break;
        }
    }
}
void animate::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render(); // clear/draw/display
    }
    cout << endl
         << "-------ANIMATE MAIN LOOP EXITING ------------" << endl;
}

string mouse_pos_string(sf::RenderWindow &window)
{
    return "(X: " +
           to_string(sf::Mouse::getPosition(window).x) +
           ", Y: " +
           to_string(sf::Mouse::getPosition(window).y) +
           ")";
}
