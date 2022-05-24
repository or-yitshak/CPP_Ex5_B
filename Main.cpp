#include <vector>
#include <string>
#include <iostream>
#include "Node.hpp"
#include "OrgChart.hpp"

using namespace std;
using namespace ariel;

int main(){
    vector<string> names = {"Bulbasaur", "Charmander", "Squirtle", "Caterpie", "Weedle", "Pidgey"};
    OrgChart organization;
    organization.add_root(names[0])
        .add_sub(names[0], names[1])
        .add_sub(names[0], names[2])
        .add_sub(names[0], names[3])
        .add_sub(names[1], names[4])
        .add_sub(names[3], names[5]);
    vector<string> exp_level_order = {names[0], names[1], names[2], names[3], names[4], names[5]};
    vector<string> exp_reverse_order = {names[4], names[5], names[1], names[2], names[3], names[0]};
    vector<string> exp_preorder = {names[0], names[1], names[4], names[2], names[3], names[5]};
    cout << endl << "start of Level order case" << endl;
    cout << "level order should be: "<<endl;
    for (size_t i = 0; i < exp_level_order.size(); i++)
    {
        cout<<exp_level_order.at(i)<<" ";
    }
    cout<<endl<< "our result: "<<endl;
    
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        cout<<(*it)<<" ";
    }
    cout << endl << "end of Level order case" << endl;
    
    cout << endl << "start of Reverse Level order case" << endl;
    cout << "reverse level order should be: "<<endl;
    for (size_t i = 0; i < exp_reverse_order.size(); i++)
    {
        cout<<exp_reverse_order.at(i)<<" ";
    }
    cout<<endl<< "our result: "<<endl;
    
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        cout<<(*it)<<" ";
    }
    cout << endl << "end of Reverse Level order case" << endl;


    cout << endl << "start of Preorder case" << endl;
    cout << "preorder should be: "<<endl;
    for (size_t i = 0; i < exp_preorder.size(); i++)
    {
        cout<<exp_preorder.at(i)<<" ";
    }
    cout<<endl<< "our result: "<<endl;
    
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {
        cout<<(*it)<<" ";
    }
    cout << endl << "end of Preorder case" << endl;


    cout << endl << "start of For Each Loop case (should be as Level order)" << endl;
    cout << "For Each Loop should be: "<<endl;
    for (size_t i = 0; i < exp_level_order.size(); i++)
    {
        cout<<exp_level_order.at(i)<<" ";
    }
    cout<<endl<< "our result: "<<endl;
     for (auto element : organization)
    { 
        cout<< element<<" ";
    } 
    cout << endl << "end of For Each Loop case" << endl;

    cout<< endl <<"demonstrate the arrow operator: "<< endl;
    cout << "should be: "<<endl;
    for (size_t i = 0; i < exp_level_order.size(); i++)
    {
        cout<<exp_level_order.at(i).size()<<" ";
    }
    cout<<endl<< "our result: "<<endl;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        cout<< it->size()<<" ";
    } 
    cout << endl << "end of demonstration" << endl;
}
