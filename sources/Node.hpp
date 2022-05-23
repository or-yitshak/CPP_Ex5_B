#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class SmartNodePtr;
class Node{
    public:
    int _level;
    string _name;
    vector<Node*> _children;

    Node(){this->_name = "null";}
    Node(Node &nd){
        this->_level = nd._level;
        this->_name = nd._name;
        for (size_t i = 0; i < nd._children.size(); i++)
        {
            Node *new_nd = new Node(*(nd._children.at(i)));
            this->_children.push_back(new_nd);
        }
        
    }
    Node &operator=(const Node & other) 
    {
        this->_level = other._level;
        this->_name = other._name;
        for (size_t i = 0; i < other._children.size(); i++)
        {
            Node *new_nd = new Node(*(other._children.at(i)));
            this->_children.push_back(new_nd);
        }
        return *this;
    }
    ~Node()
    {
        // cout<< *this<<endl;
        // cout<< "call des"<<endl;
        for (size_t i = 0; i < this->_children.size(); i++)
        {
            if (this->_children.at(i) != nullptr){
                delete this->_children.at(i);
            }
        }
        
    }
    Node(string const & name){this->_name = name;}
    Node(string const & name, int const & level){
        this->_name = name;
        this->_level = level;
        }
    friend std::ostream &operator<<(std::ostream &out, Node &nd){
        // out<< "Name: " << nd._name << endl;
        // out<< "Level: " << nd._level << endl;
        // out << "Children: [";
        // size_t len = (size_t)nd._children.size();
        // for (size_t i = 0; i < len; i++)
        // {
        //     if (i != len-1){
        //         out << nd._children.at(i)->_name << ", ";
        //     }
        //     else{
        //         out << nd._children.at(i)->_name;
        //     }
        // }
        // out << "]"<<endl;
        out<< nd._name << " => (";
        size_t len = (size_t)nd._children.size();
        for (size_t i = 0; i < len; i++)
        {
            if (i != len-1){
                out << nd._children.at(i)->_name << ", ";
            }
            else{
                out << nd._children.at(i)->_name;
            }
        }
        out << ")";
        
        
        return out;
    }
};


class SmartNodePtr {
    Node* _ptr; // Actual pointer
    public:
        // Constructor
        explicit SmartNodePtr(Node* p = nullptr) { this->_ptr = p; }
    
        // Destructor
        ~SmartNodePtr() { 
            for (size_t i = 0; i < this->_ptr->_children.size(); i++)
            {
                delete this->_ptr->_children.at(i);
            }
            delete (_ptr); }
    
        // Overloading dereferencing operator
        Node& operator*() { return *_ptr; }
    
        // Overloading arrow operator so that
        // members of T can be accessed
        // like a pointer (useful if T represents
        // a class or struct or union type)
        Node* operator->() { return _ptr; }
};