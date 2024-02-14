#ifndef NODE_H
#define NODE_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

template <typename ITEM_TYPE>
struct node
{
public:
    node(const ITEM_TYPE& item = ITEM_TYPE(), node* next = nullptr):
    _item(item), _next(next){
        const bool debug = false;
        if(debug)
            cout << "node("<<_item<<") CTOR\n";
    }
    template <typename T>
    friend std::ostream& operator <<(std::ostream& outs,
                                const node<T> &printMe);
    ITEM_TYPE _item;
    node* _next;
};

//Definitions

template <typename T>
std::ostream& operator <<(std::ostream& outs,
                                const node<T> &printMe)
{
    outs << "["<<printMe._item<<"] ->";
    return outs;    
}


#endif