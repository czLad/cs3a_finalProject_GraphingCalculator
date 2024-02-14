#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include "../node/node.h"

//Linked List General Functions:
template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE>* head);

//recursive fun! :)
template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head);

//return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head,
                                ITEM_TYPE key);


template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head,
                                ITEM_TYPE insert_this);

//insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head,
                                 node<ITEM_TYPE> *after_this,
                                 ITEM_TYPE insert_this);

//insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head,
                                  node<ITEM_TYPE>* before_this,
                                  ITEM_TYPE insert_this);

//ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head,
                                  node<ITEM_TYPE>* prev_to_this);

//delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head,
                         node<ITEM_TYPE>* delete_this);

//duplicate the list and return the last node of the copy
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head);

//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src);


//delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head);

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos);

//Zac
//inserts
template <typename ITEM_TYPE>
int _list_size(node<ITEM_TYPE>* head);

    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    //      Sorted List Routines. order: 0: ascending, order: other: descending
    //                              Assume a Sorted List
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head,       //insert
                                  ITEM_TYPE item,
                                  bool ascending=true);

//insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,
                                          ITEM_TYPE item,
                                          bool ascending=true);
//node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,
                                   ITEM_TYPE item,
                                   bool ascending=true);
//Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head);

//Remove the headptr and return the item in the node removed
template <typename ITEM_TYPE>
ITEM_TYPE _remove_head(node<ITEM_TYPE>* &head);

//Zac
//Inserts after ptr, takes after ptr by reference 
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE> *&after_this,
                                 ITEM_TYPE insert_this);

//Definitions

template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE>* head)
{
    // cout << "_print_list:\n";
    for(node<ITEM_TYPE>* walker = head; walker != nullptr; walker = walker->_next)
    {
        cout << "["<<walker->_item <<"] -> ";
    }
    cout << "|||\n";
}

template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head)
{

}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head,
                                ITEM_TYPE key)
{
    for(node<ITEM_TYPE>* walker = head; walker != nullptr; walker = walker->_next)
    {
        if(walker->_item == key)
            return walker;
    }
    return nullptr;
}


template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head,
                                ITEM_TYPE insert_this)
{
    node<ITEM_TYPE>*insert_node_ptr = new node<ITEM_TYPE>(insert_this);
    insert_node_ptr->_next = head;
    head = insert_node_ptr;
    return head;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head,
                                 node<ITEM_TYPE> *after_this,
                                 ITEM_TYPE insert_this)
{
    if(head == nullptr)
        return _insert_head(head, insert_this);
    else
    {
        if(after_this == nullptr)
            return _insert_head(head, insert_this);
        node<ITEM_TYPE>*insert_node_ptr = new node<ITEM_TYPE>(insert_this);
        insert_node_ptr->_next = after_this->_next;
        after_this->_next = insert_node_ptr;
        return insert_node_ptr;
    }

}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head,
                                  node<ITEM_TYPE>* before_this,
                                  ITEM_TYPE insert_this)
{
    if(head == nullptr)
    {
        return _insert_head(head, insert_this);
    }
    else
    {
        node<ITEM_TYPE>*prev_node = _previous_node(head, before_this);
        return _insert_after(head, prev_node, insert_this);
    }
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head,
                                  node<ITEM_TYPE>* prev_to_this)
{
    if(head == nullptr)
        return nullptr;
    
    if(head == prev_to_this)
        return nullptr;

    node<ITEM_TYPE>*walker;
    for(walker = head; walker != nullptr; walker = walker->_next)
    {
        if(walker->_next == prev_to_this)
            return walker;
    }    
    assert(walker != nullptr && "Key cannot be found in list.");
}

template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head,
                         node<ITEM_TYPE>* delete_this)
{
    if(head == delete_this)
        return _remove_head(head);
    else
    {
        ITEM_TYPE deleted_item = delete_this->_item;
        node<ITEM_TYPE>* prev_node = _previous_node(head, delete_this);
        prev_node->_next = delete_this->_next;
        delete delete_this;

        return deleted_item;
    }
}

template <typename ITEM_TYPE> //returns address of last node
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head)
{
    node<ITEM_TYPE>* copy_head = nullptr;
    copy_head = _copy_list(copy_head, head);

    return copy_head;
}

template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src)
{
    _clear_list(dest);
    if(src == nullptr)
        return nullptr;
    node<T>* src_walker = src;
    dest = new node<T>(src_walker->_item);
    node<T>* dest_walker = dest;

    for(src_walker = src->_next; src_walker != nullptr; src_walker = src_walker->_next)
    {
        dest_walker->_next = new node<T>(src_walker->_item);
        dest_walker = dest_walker->_next;
    }

    return dest_walker;
}

template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head)
{
    while(head != nullptr)
        _remove_head(head);
}

template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos)
{
    int size = 0;
    for(node<ITEM_TYPE>* walker = head; walker != nullptr; walker = walker->_next)
    {
        if(size == pos)
            return walker->_item;
        size++;
    }
    assert(pos < size && "Index must be less than size.");
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head,       //insert
                                  ITEM_TYPE item,
                                  bool ascending)
{
    node<ITEM_TYPE>* node_to_insert_aft = _where_this_goes(head, item, ascending);
    if(node_to_insert_aft == nullptr)
        return _insert_head(head, item);
    else
        return _insert_after(head, node_to_insert_aft, item);
}

//insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,
                                          ITEM_TYPE item,
                                          bool ascending)
{
    node<ITEM_TYPE>* node_to_insert_aft = _where_this_goes(head, item, ascending);
    if(node_to_insert_aft == nullptr)
        return _insert_head(head, item);
    else if(node_to_insert_aft->_item == item)
    {
        node_to_insert_aft->_item += item;
        return node_to_insert_aft;
    }
    else
        return _insert_after(head, node_to_insert_aft, item);
    return head;
}
//node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,
                                   ITEM_TYPE item,
                                   bool ascending)
{
    if(head == nullptr)
        return nullptr;
    node<ITEM_TYPE>* lead_walker = head;
    node<ITEM_TYPE>* follow_walker = head;
    if(ascending)
    {
        if(lead_walker->_item > item)
            return nullptr;
    }
    else
    {
        if(lead_walker->_item < item)
            return nullptr;
    }
    for(lead_walker = lead_walker->_next; lead_walker != nullptr; lead_walker = lead_walker->_next)
    {
        if(ascending)
        {
            if(lead_walker->_item > item)
                return follow_walker;
        }
        else
        {
            if(lead_walker->_item < item)
                return follow_walker;
        }
        follow_walker = follow_walker->_next;
    }
    return follow_walker;

}
//Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head)
{
    if(head == nullptr)
        return nullptr;
    for(node<ITEM_TYPE>* walker = head; walker != nullptr; walker = walker->_next)
    {
        if(walker->_next == nullptr)
            return walker;
    }
}

template <typename ITEM_TYPE>
ITEM_TYPE _remove_head(node<ITEM_TYPE>* &head)
{
    assert(head != nullptr && "Linked list cannot be empty.");
    ITEM_TYPE removed_item = head->_item;
    node<ITEM_TYPE>* remove_ptr = head;
    head = remove_ptr->_next;
    delete remove_ptr;
    remove_ptr = nullptr;

    return removed_item;
}

template <typename ITEM_TYPE>
int _list_size(node<ITEM_TYPE>* head)
{
    int size = 0;
    for(node<ITEM_TYPE>* walker = head; walker != nullptr; walker = walker->_next)
    {
        size++;
    }
    return size;
}

// template <typename ITEM_TYPE>
// node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE> *&after_this,
//                                  ITEM_TYPE insert_this)
// {
//     node<ITEM_TYPE>*insert_node_ptr = new node<ITEM_TYPE>(insert_this);
//     insert_node_ptr->_next = after_this->_next;
//     after_this->_next = insert_node_ptr;
//     return insert_node_ptr;
// }

//Backups

// template <typename ITEM_TYPE>
// void _clear_list(node<ITEM_TYPE>*& head)
// {
//     const bool debug = false;
//     if(head != nullptr)
//     {
//         for(node<ITEM_TYPE>* walker = head->_next; walker != nullptr; walker = walker->_next)
//         {
//             if(debug)
//             {
//                 cout << "where walker is at before removing: " << *walker << "\n";
//                 cout << "heads to be removed: " << *head << "\n";
//             }
        
//             if(debug)
//                 cout << "_remove_head(head): "<<_remove_head(head)<<"\n";
//             else
//                 _remove_head(head);
        
//             if(debug)
//             {
//                 if(walker->_next != nullptr)
//                 cout << "where walker is going after removing: " << *(walker->_next)<< "\n";
//             }
//         }
//         if(debug)
//             cout << "_remove_head(head): "<<_remove_head(head)<<"\n";
//         else
//             _remove_head(head);
//     }    
// }

// template <typename ITEM_TYPE>
// node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head)
// {
//     if(head == nullptr)
//         return nullptr;
//     node<ITEM_TYPE>* head_walker = head;
//     node<ITEM_TYPE>* copy_head = new node<ITEM_TYPE>(head_walker->_item);
//     node<ITEM_TYPE>* copy_walker = copy_head;

//     for(head_walker = head->_next; head_walker != nullptr; head_walker = head_walker->_next)
//     {
//         copy_walker->_next = new node<ITEM_TYPE>(head_walker->_item);
//         copy_walker = copy_walker->_next;
//     }
    
//     return copy_head;
// }

// template <typename T>
// node<T> *_copy_list(node<T>* &dest, node<T> *src)
// {
//     // assert(dest != nullptr && "Destination list cannot be empty");
//     //algorithm returns nullptr if src is nullptr

//     node<T>* copy_head = _copy_list(src);
//     _clear_list(dest);
//     dest = copy_head;

//     return _last_node(dest);
// }


#endif