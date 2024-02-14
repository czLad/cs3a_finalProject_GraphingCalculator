#include "sidebar.h"
#include "constants.h"
Sidebar::Sidebar()
{
}

Sidebar::Sidebar(float left, float width, int payload_size) : _left(left), _width(width)
{
    _TOP_MARGIN = 10;
    _VERTICAL_LINE_SPACING = 30.0;
    _fileout = Fileout("history1.txt"); //Just gives Filein object filename does not open or close file
    _previous_records_out = Fileout("previous_record1.txt"); //Saves _begin_readline's last position
    _previous_records_in = Filein("previous_record1.txt");
    _previous_records_in.open_file();
    _begin_readline = stoi(_previous_records_in.read_from_file());
    _init_begin_readline = _begin_readline; 
    _previous_records_in.close_file();

    _PAYLOAD_SIZE = payload_size;
    cout << "Sidebar CTOR: TOP" << endl;
    items.reserve(50);

    // set up the sidebar rectangle:
    rect.setFillColor(sf::Color(105, 105, 105)); //(192,192,192)); //silver
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    cout << "Sidebar CTOR: about to load font." << endl;

    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // the font file must be in the "working directory"
    //  check projects->run->working directory
    //       [Make sure it's not pointing to the app file]

    if (!font.loadFromFile("Roboto-Thin.ttf"))
    {
        cout << "Sidebar() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    cout << "Sidebar CTOR: loaded font." << endl;

    //. . . . . text / font problems: . . . . . . . .
    // initializing text object in this way caused problems
    // (hangs!)
    // only when sb_text was a private member and worked fine
    // when it was a public member. Probably not releavant,
    // but still strange!
    //
    // sb_text = sf::Text("Initial String for myTextLabel", font);
    //
    //. . . . . . . . . . . . . . . . . . . . . . . . .
    cout << "Sidebar CTOR: Text object initialized." << endl;
    sb_text.setFont(font);
    sb_text.setCharacterSize(18);
    sb_text.setStyle(sf::Text::Bold);
    sb_text.setFillColor(sf::Color::Yellow);

    ////this is how you would position text on screen:
    // sb_text.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-sb_text.getLocalBounds().height-5));

    items.push_back("sidebar sample text");
    items.push_back("");
    // Fill the items vector with empty strings so that we can use [] to read them:
    // for (int i = 0; i < 1; i++)
    // {
    //     items.push_back("");
    // }
    _bounds._X_lower_bound = WORK_PANEL;
    _bounds._X_upper_bound = SCREEN_WIDTH;
    _bounds._Y_lower_bound = _TOP_MARGIN + items.size() * _VERTICAL_LINE_SPACING;
    // _bounds._Y = _TOP_MARGIN + items.size() * _VERTICAL_LINE_SPACING;

    _filein = Filein("history1.txt");
    update();
    cout << "Sidebar: CTOR: Exit." << endl;

}

void Sidebar::draw(sf::RenderWindow &window)
{
    const double LEFT_MARGIN = 10.0;

    window.draw(rect);
    float height = _TOP_MARGIN;

    //Displaying Utilities
    for (vector<string>::iterator it = items.begin();
         it != items.end(); it++)
    {
        sb_text.setString(it->c_str());
        sb_text.setPosition(sf::Vector2f(_left + LEFT_MARGIN, height));
        // Divides sidebar into even portions
        height += _VERTICAL_LINE_SPACING;
        window.draw(sb_text);
    }

    for (vector<graph_payload>::iterator it = payloads.begin();
         it != payloads.end(); it++)
    {
        bool blank = false;
        if (it->_equation.length() == 0)
        {
            // empty rows must be taken into account (getLocalBounds())
            //     but not drawn
            blank = true;
            sb_text.setString("BLANK");
        }
        else
        {
            sb_text.setString(it->_equation.c_str());
        }
        // Divides sidebar into even portions
        sb_text.setPosition(sf::Vector2f(_left + LEFT_MARGIN, height));
        // Text Rect Size
        // sb_text_rect.setSize(sf::Vector2f(_width - 10, sb_text.getLocalBounds().height));
        height += _VERTICAL_LINE_SPACING;
        if (!blank)
            window.draw(sb_text);
            // window.draw(sb_text);
    }
}

//Gives access to payload at index
graph_payload& Sidebar::operator[](int index)
{
    return payloads[index];
}
