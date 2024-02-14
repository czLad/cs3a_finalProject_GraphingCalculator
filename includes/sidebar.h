#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "filein.h"
#include "fileout.h"
#include "graph_payload.h"
#include "constants.h"
#include "window_bounds.h"

using namespace std;

// Sidebar takes a default of 4 payloads
// Users of the class are required to have a tokenizer (12/10/23)
// Users of the class are required to have a minimum of 4 payloads recorded in a history.txt (12/10/23)
// Users of the class are required to have two lines and zero written on first line on a previous_record.txt (12/10/23)

class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width, int payload_size = 4);
    void draw(sf::RenderWindow& window);
    //v Can be used later for delete
    // string& operator [](int index);
    graph_payload& operator [](int index);
    // Animate event handler uses these getters to calculate which payload is wanted 
    int get_TOP_MARGIN(){return _TOP_MARGIN;}
    int get_VERTICAL_LINE_SPACING() {return _VERTICAL_LINE_SPACING;}
    string& set_utilities(int index)
    {
        return items[index];
    }
    // Discounts the extra utilities and make click correspond to index
    int get_utilities_size(){return items.size();}
    void push_payload(const string& equation, 
    const double& domain_lower_bound, const double& domain_upper_bound
    ,const double& y_lower_bound, const double& y_upper_bound)
    {
        // Writing part still hard coded. No certain idea how to parameterize.
        _begin_readline += example_payload._size; // Later 1 is to be payload._size //payloads[i] can be any index within size
        for(int i = 0; i < example_payload._size; i++) // Later 1 is to be payload._size
        {
            if(i == 0)
                _fileout.write_to_file("eq:"+equation); // Payload object needs to provide delimiters for all of its member variables
            else if(i == 1)
                _fileout.write_to_file("d:"+to_string(domain_lower_bound)+","+to_string(domain_upper_bound));
            else if(i == 2)
                _fileout.write_to_file("y:"+to_string(y_lower_bound)+","+to_string(y_upper_bound));
        }
        update();
    }
    // Updates the payload vector
    void update()
    {
        payloads.clear();
        _filein.open_file();
        // First loop skips unwanted payloads
        for(int i = 0; i < _begin_readline; i++)
        {
            _filein.read_from_file();
        }
        // Second loop reads into payload vector
        for(int i = 0; i < _PAYLOAD_SIZE; i++)
        {
            graph_payload g_pyld;
            for(int j = 0; j < example_payload._size; j++)
            {
                g_pyld.tokenizer(_filein.read_from_file());
            }
            // Although not implemented can know where file ends here
            if(!g_pyld.is_empty())
                payloads.push_back(g_pyld);
        }
        _filein.close_file();
        _previous_records_out.overwrite_to_file(to_string(_begin_readline));
        _bounds._Y_upper_bound = _bounds._Y_lower_bound + payloads.size() * _VERTICAL_LINE_SPACING;
    }
    void set_payload_size(int payload_size){_PAYLOAD_SIZE = payload_size;}
    void scroll_up()
    {
        // Does not allow user to scroll up past the first line of file
        if(_begin_readline > 0)
        {
            _begin_readline -= example_payload._size;
            update();
        }
    }
    void scroll_down()
    {
        // Allow user to scroll down as much as you want
        // But payload vector does not load any empty payloads
        _begin_readline += example_payload._size;
        update();
    }
    void scroll_default()
    {
        // Puts begin readline to the line user last left off
        _begin_readline = _init_begin_readline;
        update();
    }
    graph_payload atMousePos(const int& mpos_x, const int& mpos_y)
    {
        // Calculates where string is located on sidebar and
        // relates that location to the index of respective payloads
        // in the payload vector
        graph_payload g_pyld;
        int mpos_y_for_pyld = mpos_y - (_TOP_MARGIN + items.size() * _VERTICAL_LINE_SPACING);
        int index = mpos_y_for_pyld / _VERTICAL_LINE_SPACING;
        g_pyld._equation = payloads[index]._equation;
        g_pyld._domain._lower_bound = payloads[index]._domain._lower_bound;
        g_pyld._domain._upper_bound = payloads[index]._domain._upper_bound;
        g_pyld._y_axis._lower_bound = payloads[index]._y_axis._lower_bound;
        g_pyld._y_axis._upper_bound = payloads[index]._y_axis._upper_bound;
        return g_pyld;
    }
    // Gets the bounds of where one can access payloads by clicking on sidebar
    WindowBounds get_bounds(){return _bounds;}
    // Needs to allow user to access utilities in future updates
private:
    sf::RectangleShape rect;            //sidebar rectangle
    vector<string> items;               //strings to place on the sidebar
    //Zac
    vector<graph_payload> payloads;

    sf::Font font;                      //used to draw text
    sf::Text sb_text;                   //used to draw strings on the window object

    //Zac
    Filein _filein;
    Fileout _fileout;
    int _begin_readline;
    int _end_readline;
    int _TOP_MARGIN;
    double _VERTICAL_LINE_SPACING;
    int _PAYLOAD_SIZE;
    Filein _previous_records_in;           //If using sidebar for first time clear previous_record.txt and write 0
    Fileout _previous_records_out;
    float _left;
    float _width;
    int _init_begin_readline;

    //templated later
    graph_payload example_payload;
    WindowBounds _bounds;
};

#endif // SIDEBAR_H
