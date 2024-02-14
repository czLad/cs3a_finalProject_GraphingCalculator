#ifndef WINDOW_BOUNDS_H
#define WINDOW_BOUNDS_H

#include <iostream>
#include <iomanip>

using namespace std;

struct WindowBounds
{
public:
    //lower upper can be turn into a struct later
    int _X_lower_bound;
    int _X_upper_bound;
    int _Y_lower_bound;
    int _Y_upper_bound;
    WindowBounds(): _X_lower_bound(0), _X_upper_bound(0), _Y_lower_bound(0), _Y_upper_bound(0) {}
    WindowBounds(int X_lower_bound, int X_upper_bound, int Y_lower_bound, int Y_upper_bound): 
    _X_lower_bound(X_lower_bound), _X_upper_bound(X_upper_bound), _Y_lower_bound(Y_lower_bound) ,_Y_upper_bound(Y_upper_bound) {}
    bool contains(int mpos_x, int mpos_y)
    {
        if(mpos_x < _X_upper_bound && mpos_x > _X_lower_bound && mpos_y < _Y_upper_bound && mpos_y > _Y_lower_bound)
            return true;
        else
            return false;
    }
    friend ostream& operator << (ostream& outs, const WindowBounds& other)
    {
        // outs<<"hi domain\n";
        outs<<"Bounds: [ X: ("<<other._X_lower_bound<<","<<other._X_upper_bound<<")"<<" | Y: ("
        <<other._Y_lower_bound<<","<<other._Y_upper_bound<<")";
        return outs;
    }  
};


#endif