#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "iostream"
#include "iomanip"
#include <SFML/Graphics.hpp>
#include "sstream"
#include "graph_info.h"
#include "fileout.h"
#include "sidebar.h"
#include "cassert"
#include "error_code.h"

#define DELETE_KEY 8
#define B_KEY 66
#define ENTER_KEY 13
#define C_KEY 99

using namespace std;

class Textbox
{
public:
    Textbox(): _is_selected(false), _has_limit(false){}
    Textbox(int size, sf::Color color, bool sel, graph_info* info, Sidebar* sidebar)
    {
        _sidebar = sidebar;
        _textbox.setCharacterSize(size);
        _textbox.setColor(color);
        _is_selected = sel;
        _info = info;
        // _file = Fileout("history.txt");

        if(!_textbox_bg_txt.loadFromFile("Textbox7.png"))
        {
            cout << "_textbox_bg_txt failed to load.\n";
            exit(-1);
        }
        test_sprite.setPosition(sf::Vector2f(0, -20));
        test_sprite.setScale(sf::Vector2f(0.14, 0.06));
        
        if(_is_selected)
        {
            _textbox.setString("_");
        }
        else
        {
            _textbox.setString("");
        }
    }
    void set_font(sf::Font &font)
    {
        _textbox.setFont(font);
    }
    void set_position(sf::Vector2f pos)
    {
        _textbox.setPosition(pos);
    }
    void set_limit(const int& limit)
    {
        _has_limit = true;
        _limit = limit + 1;
    }
    void set_selected(bool sel)
    {
        _is_selected = sel;
        if(!_is_selected)
        {
            std::string t = _text.str();
            std::string new_t = "";
            _textbox.setString(new_t);
            _text.str("");
            _text<<new_t;
        }
    }
    bool get_is_selected()
    {
        return _is_selected;
    }
    std::string getText()
    {
        return _text.str();
    }
    void Draw(sf::RenderWindow &window)
    {
        if(_is_selected)
        {
            test_sprite.setTexture(_textbox_bg_txt);
            window.draw(test_sprite);
            window.draw(_textbox);
        }
    }
    void type_on(sf::Event input) throw(Error_Code)
    {
        if(_is_selected)
        {
            // cout << "type_on -> _is_selected.\n";
            int charTyped = input.text.unicode;
            if(charTyped < 128)
            {
                if(_has_limit)
                {
                    // cout <<"_text.str(): ";
                    // cout << _text.str();
                    // cout << "\n";
                    if(_text.str().length() <= _limit)
                    {
                        // cout << "_text.str().length() <= _limit\n";
                        _input_logic(charTyped);
                    }
                    else if(_text.str().length() > _limit && charTyped == DELETE_KEY)
                    {
                        // cout << "_text.str().length() > _limit && charTyped == DELETE_KEY\n";
                        _delete_last_char();
                    }
                    else if(_text.str().length() > _limit)
                    {
                        // cout << "_text.str().length() > _limit\n";
                    }
                }
                else
                    _input_logic(charTyped);
            }
        }
    }
    void set_is_key_for_call(const bool& is_k_for_cl) {_is_key_for_call = is_k_for_cl;}
private:
    sf::Text _textbox;
    std::ostringstream _text;
    bool _is_selected;
    bool _has_limit;
    int _limit;
    graph_info* _info;
    bool was_ENTER_KEY;
    bool _is_key_for_call;
    sf::RectangleShape _textbox_bg;
    sf::Texture _textbox_bg_txt;
    sf::Sprite test_sprite;
    Fileout _file;
    Sidebar* _sidebar;

    void _input_logic(int charTyped) throw(Error_Code)
    {
        // Putting into _text(ostringstream) for realtime display
        if(charTyped != DELETE_KEY && charTyped != ENTER_KEY && !_is_key_for_call)
        {
            _text << static_cast<char>(charTyped);
        }
        // Removing last char
        else if(charTyped == DELETE_KEY)
        {
            // cout << "charTyped == DELETE_KEY\n";
            was_ENTER_KEY = false;
            if(_text.str().length() > 0)
            {
                _delete_last_char();
            }
        }
        // Assigining _text to _info_equation to change graph
        else if(charTyped == ENTER_KEY)
        {
            // Checking if empty string and if so just close text box
            if(_text.str().size() >= 1)
            {
                _sidebar->push_payload(_info->_equation, _info->_d._lower_bound, _info->_d._upper_bound, 
                _info->y_axis._lower_bound, _info->y_axis._upper_bound);
                //Checks if input is valid or not
                if(inspect_eq(_text.str()))
                    _info->_equation = _text.str();
            }
            set_selected(false);
        }
        // Keeps displaying underscore if textbox is selected
        if(_is_selected)
            _textbox.setString(_text.str() + "_");
    }
    // Delete logic for textbox
    // Loops one less index
    void _delete_last_char()
    {
        std::string t = _text.str();
        std::string new_t = "";
        // Adds to new_t one less index of t
        for(int i = 0; i < t.length() - 1; i++)
        {
            new_t += t[i];
        }
        // Clears _text.str()
        _text.str("");
        // Puts new deleted string to _text
        _text << new_t;
        
        _textbox.setString(_text.str());
    }
    bool inspect_eq(string equation) throw (Error_Code)
    {
        const bool debug = false;
        if(debug)
            cout << "inspect_eq\n";
        Error_Code error_code;
        string divison_check_str = "";
        // v Creates a replica of string equation in argument, can use to debug
        string test_str;
        if(debug)
            test_str = "test str:";
        int left_paren_count = 0;
        int right_paren_count = 0; 
        bool was_division = false;
        for(int i = 0; i < equation.size(); i++)
        {
            if(equation[i] == '(')
                left_paren_count++;
            else if(equation[i] == ')')
                right_paren_count++;
            else if(equation[i] == '/')
            {
                was_division = true;
            }
            if(was_division)
            {
                divison_check_str += equation[i];
            }

            if(divison_check_str == "/0")
            {
                divison_check_str = "";
                set_selected(false);
                error_code._code = 1; //Zero Division
                throw error_code;
            }
            if(debug)
                test_str += equation[i];
        }
        if(debug)
            cout << test_str << "\n";
        if(right_paren_count < left_paren_count)
        {
            set_selected(false);
            error_code._code = 3; //Missing right paren
            throw error_code;
        }
        if(left_paren_count < right_paren_count)
        {
            set_selected(false);
            error_code._code = 2; //Missing left paren
            throw error_code;
        }
        return true;
    }
};


#endif