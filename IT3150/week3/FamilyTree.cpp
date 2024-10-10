/*
Given a family tree represented by child-parent (c,p) relations in which c is a child of p. Perform queries about the family tree:
descendants <name>: return number of descendants of the given <name>
generation <name>: return the number of generations of the descendants of the given <name>

Note that: the total number of people in the family is less than or equal to 10
4
Input
Contains two blocks. The first block contains information about child-parent, including lines
(terminated by a line containing ***),
 each line contains: <child> <parent> where <child> is a string represented
 The second block contains lines (terminated by a line containing ***),
 each line contains two string <cmd> and <param> where <cmd> is the command
 (which can be descendants or generation) and <param> is the given name of the person participating in the  query.
Output
Each line is the result of a corresponding query.
Example
Input
Peter Newman
Michael Thomas
John David
Paul Mark
Stephan Mark
Pierre Thomas
Mark Newman
Bill David
David Newman
Thomas Mark
***
descendants Newman
descendants Mark
descendants David
generation Mark
***
Output
10
5
2
2
*/
#include<bits/stdc++.h>
using namespace std;
map< string, string> relation;
map< string, int> generation;
map< string, int> num_childs;

void updateGen(string child, string parent){
    relation[child]= parent;
        while(generation[child] == generation[relation[child]]){
            generation[relation[child]]++;
            child = relation[child];
        }
        return;
}
void updateNumChild( string child, string parent){
    int add = num_childs[child]+1;
    num_childs[parent]= num_childs[parent] + add;
    child= relation[child];
    while(relation[child] != ""){
        child = relation[child];
        num_childs[child]+= add ;
    }
    return;
}
int main(){
    string child, parent;
    while( true){
        cin>> child;
        if(child== "***"){
            break;
        }
        cin>> parent;
        updateGen(child, parent);
        updateNumChild (child,parent);
    }


    string control;
    while(true){
        cin>> control;
        if(control=="***"){
            break;
        }
        else if( control =="descendants"){
            string name;
            cin>> name;
            cout <<  num_childs[name] << endl;

        }
        else if( control =="generation"){
            string name;
            cin>> name;
            cout<< generation[name] <<endl;
        }
    }
    return 0;
}

