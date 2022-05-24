#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class Node
{
public:
    int _level = 0;
    string _name = "null";
    vector<Node *> _children;

    Node() {}
    Node(string const &name, int const &level)
    {
        this->_name = name;
        this->_level = level;
    }
    Node(Node const &nd)
    {
        this->_level = nd._level;
        this->_name = nd._name;
        for (size_t i = 0; i < nd._children.size(); i++)
        {
            Node *new_nd = new Node(*(nd._children.at(i)));
            this->_children.push_back(new_nd);
        }
    }
    Node(Node &&other) noexcept
    {
        // this->_root = other._root;
        // other._root = nullptr;
        if (this == &other)
        {
            return;
        }
        this->_level = other._level;
        this->_name = other._name;
        for (size_t i = 0; i < other._children.size(); i++)
        {
            Node *new_nd = new Node(*(other._children.at(i)));
            this->_children.push_back(new_nd);
        }
        delete (&other);
    }
    Node &operator=(const Node &other)
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
    Node &operator=(Node &&other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        this->_level = other._level;
        this->_name = other._name;
        for (size_t i = 0; i < other._children.size(); i++)
        {
            Node *new_nd = new Node(*(other._children.at(i)));
            this->_children.push_back(new_nd);
        }
        delete (&other);
        return *this;
    }
    ~Node()
    {
        for (size_t i = 0; i < this->_children.size(); i++)
        {
            if (this->_children.at(i) != nullptr)
            {
                delete this->_children.at(i);
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &out, Node &nd)
    {
        out << nd._name << " => (";
        size_t len = (size_t)nd._children.size();
        for (size_t i = 0; i < len; i++)
        {
            if (i != len - 1)
            {
                out << nd._children.at(i)->_name << ", ";
            }
            else
            {
                out << nd._children.at(i)->_name;
            }
        }
        out << ")";

        return out;
    }
};
