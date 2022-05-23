#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <queue>
#include "Node.hpp"
#pragma once

using namespace std;

namespace ariel
{
    class OrgChart{
        public:
        Node* _root = nullptr;
        size_t _size = 0;
        OrgChart(){}
        OrgChart(OrgChart const &other)
        {
            this->_root = new Node(*(other._root));
        }

        static Node* findND(Node* nd, string const & str);
        OrgChart add_root(string const & str);
        OrgChart add_sub(string const & parent,string const & child);
        friend std::ostream &operator<<(std::ostream &out, OrgChart &og);
        class Iterator {
            private:
                Node *_ptr;
                queue<Node*> _q;
               
                void initLevelOrder();
                void initReverseLevelOrder();
                void initPreOrder(Node* nd);
            public:
                Iterator(Node *p){
                    _ptr = p;
                }

                Iterator(Node *p,int how){
                    _ptr = p;
                    if (how == 1){
                        this->initLevelOrder();
                    }
                    else if (how == 2){
                        this->initReverseLevelOrder();
                    }
                    else if (how == 3){
                        this->initPreOrder(p);
                        this->_q.pop();
                    }
                }

                Iterator & operator++() {
                    if(this->_q.empty()){
                        this->_ptr = nullptr;
                    }
                    else{
                        this->_ptr = this->_q.front();
                        this->_q.pop();
                    }
                    return *this;
                }
                Iterator & operator++(int) {
                    if(this->_q.empty()){
                        this->_ptr = nullptr;
                    }
                    else{
                        this->_ptr = this->_q.front();
                        this->_q.pop();                        
                    }
                    return *this;
                }
                string operator*() const {return this->_ptr->_name;}
                bool operator!=(const Iterator & other) const {return this->_ptr != other._ptr;}
                bool operator==(const Iterator & other) const {return this->_ptr == other._ptr;}
                string* operator->() const {return &(this->_ptr->_name); }
                // ~Iterator(){
                //     delete this->_ptr;
                //     while (!this->_q.empty())
                //     {
                //         delete this->_q.front();
                //         this->_q.pop();
                //     }
                    
                // }
                
        };
        OrgChart:: Iterator begin_level_order()const;
        OrgChart:: Iterator end_level_order()const;
        OrgChart:: Iterator begin_reverse_order()const;
        OrgChart:: Iterator reverse_order()const;//end
        OrgChart:: Iterator begin_preorder()const;
        OrgChart:: Iterator end_preorder()const;
        OrgChart:: Iterator begin()const;
        OrgChart:: Iterator end()const;


        OrgChart &operator=(const OrgChart & other) 
        {
            this->_root = new Node(*(other._root));
            return *this;
        }
        ~OrgChart(){
            if (this->_root != nullptr){
                cout<< "call destructor!"<<endl;
                cout<<*(this->_root)<<endl;
                cout<<this->_root<<endl;
                cout<< "end of destructor!"<<endl;
                delete (this->_root);
            }
        }
    };
   
}