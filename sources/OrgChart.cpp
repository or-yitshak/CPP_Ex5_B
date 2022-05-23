#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <stack> 

#include "OrgChart.hpp"
#include "Node.hpp"

using namespace std;
using namespace ariel;

Node*  OrgChart:: findND(Node* &nd, string const & str)
{
    if (nd->_name == str){
        cout<<"found: "<<nd<<" "<<*nd<<" ";
        return nd;
    }
    if (nd == nullptr){
        return nullptr;
    }
    Node *curr_find = nullptr;
    for (size_t i = 0; i < nd->_children.size(); i++)
    {
        Node *curr_child = nd->_children.at(i);
        curr_find = findND(curr_child,str);
        if (curr_find != nullptr)
        {
            break;
        }        
    }
    cout<<"found: "<<curr_find;//<<" "<<*curr_find<<" ";
    if(curr_find!=nullptr){
        cout<<" "<<*curr_find<<" ";
    }
    return curr_find;
    
}
OrgChart& OrgChart:: add_root(string const & str)
{
    if (this->_root == nullptr){
        this->_root = new Node(str,0);
        this->_size++;
    }
    else{
        // cout << *(this->_root)<<endl;
        // Node *tmp = new Node(*(this->_root));
        // cout << *(tmp)<<endl;
        // // delete this->_root;
        // this->_root = tmp;
        this->_root->_name = str;
    }
    cout<<"root: "<<this->_root<<" "<<*(this->_root)<<endl;
    return *this;
}
OrgChart& OrgChart:: add_sub(string const & parent,string const & child)
{
    if (this->_root == nullptr){
        throw invalid_argument("root is null!");
    }
    cout<<endl<<"before found "<<this->_root<<endl;
    Node *parent_nd = findND(this->_root,parent);
    if (parent_nd == nullptr){
        throw invalid_argument("this parent: "+ parent +" is not a member in orgchart");
    }
    // for (size_t i = 0; i < parent_nd->_children.size(); i++)
    // {
    //     if(parent_nd->_children.at(i)->_name == child){
    //         throw invalid_argument("this child: "+ parent +" is alredy a child of: "+ parent);
    //     }
    // }
    Node *child_nd = nullptr;
    child_nd = new Node(child,parent_nd->_level+1);
    parent_nd->_children.push_back(child_nd);    
    this->_size++;
    cout<<"parent: "<<parent_nd<<" " <<*parent_nd<<endl;//<<" child: "<<this->_root<<endl;

    return *this;
}

OrgChart:: Iterator OrgChart:: begin_level_order()const{
    if (this->_root == nullptr){
        throw invalid_argument("root is null!");
    }
    int const LEVEL = 1;
    OrgChart:: Iterator it(this->_root,LEVEL);
    return it;
}
void OrgChart:: Iterator:: initLevelOrder()
{
    queue<Node*> q;
    q.push(this->_ptr);
    Node *curr_nd = nullptr;
    while (!q.empty())
    {
        curr_nd = q.front();
        q.pop();
        this->_q.push(curr_nd);
        for (size_t i = 0; i < curr_nd->_children.size(); i++)
        {
            Node *curr_child = curr_nd->_children.at(i);
            q.push(curr_child);
        }        
    }
    this->_q.pop();    
}

OrgChart:: Iterator OrgChart:: end_level_order()const{
    if (this->_root == nullptr){
        throw invalid_argument("root is null!");
    }
    OrgChart:: Iterator it(nullptr);
    return it;
}
OrgChart:: Iterator OrgChart:: begin_reverse_order()const{
    if (this->_root == nullptr){
        throw invalid_argument("root is null!");
    }
    int const REVERSE_LEVEL = 2;
    OrgChart:: Iterator it(this->_root,REVERSE_LEVEL);
    return it;
}

void OrgChart:: Iterator:: initReverseLevelOrder()
{
    stack<Node*> st;
    this->_q.push(this->_ptr);
    Node *curr_nd = nullptr;
    while (!this->_q.empty())
    {
        curr_nd = this->_q.front();
        this->_q.pop();
        st.push(curr_nd);
        size_t s = curr_nd->_children.size();
        for (size_t i = 0; i < s; i++)
        {
            Node *curr_child = curr_nd->_children.at(s-1-i);
            this->_q.push(curr_child);
        }        
    }
    while (!this->_q.empty())
    {
        Node *curr_nd =this->_q.front();
        this->_q.pop();
        st.push(curr_nd);
    }
     while (!st.empty())
    {
        Node *curr_nd =st.top();
        st.pop();
        this->_q.push(curr_nd);
    }
    this->_ptr = this->_q.front();
    this->_q.pop();
    
}

OrgChart:: Iterator OrgChart:: reverse_order()const{   
    if (this->_root == nullptr){
        throw invalid_argument("root is null!");
    }
    OrgChart:: Iterator it(nullptr);
    return it;
}
OrgChart:: Iterator OrgChart:: begin_preorder()const{
    if (this->_root == nullptr){
        throw invalid_argument("root is null!");
    }
    int const PREORDER = 3;
    OrgChart:: Iterator it(this->_root,PREORDER);
    return it;
}

void OrgChart:: Iterator:: initPreOrder(Node* nd){
    if(nd == nullptr) {return;}
    this->_q.push(nd);
    for (size_t i = 0; i < nd->_children.size(); i++)
    {
        Node *curr_child = nd->_children.at(i);
        initPreOrder(curr_child);
    }
}

OrgChart:: Iterator OrgChart:: end_preorder()const{
    if (this->_root == nullptr){
        throw invalid_argument("root is null!");
    }
    OrgChart:: Iterator it(nullptr);
    return it;
}
OrgChart:: Iterator OrgChart:: begin()const{
    return begin_level_order();
}
OrgChart:: Iterator OrgChart:: end()const{
    return end_level_order();
}

ostream & ariel::operator<<(ostream &out, OrgChart &og){
    out << endl;
    queue<Node*> q;
    q.push(og._root);
    Node *curr_nd = nullptr;
    int level = 0;
    out << "Level 0: ";
    while (!q.empty())
    {
        curr_nd = q.front();
        q.pop();
        int curr_level = curr_nd->_level;
        if(curr_level != level){
            level = curr_level;
            out<<endl;
            out << "Level "<< level<<": ";
        }        
        out<< *curr_nd;
        if(!q.empty() && q.front()->_level == level){
            out<<", ";
        }
        for (size_t i = 0; i < curr_nd->_children.size(); i++)
        {
            Node *curr_child = curr_nd->_children.at(i);
            q.push(curr_child);
        }        
    }
    out << endl;
    return out;
};