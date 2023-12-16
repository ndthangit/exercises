#ifndef COLORING_H
#define COLORING_H

#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

vector<vector<long>> vectors;

string colors[] = {
        "beige","red", "blue", "green", "yellow", "orange", 
        "purple", "pink", "black", "white", "gray", 
        "brown", "cyan", "magenta", "lime", "olive", 
        "maroon", "navy", "teal", "silver", "gold", 
        "indigo", "turquoise", "violet", "coral", "ivory", 
        "lavender", "salmon", "aquamarine", "crimson", "fuchsia", 
        "khaki", "orchid", "plum", "sienna", "tan", 
        "thistle", "tomato", "wheat",  "slate"
    };

void create(fstream &input, long quantityOfEdge){
    //tạo cây thông qua các cạnh
    for (int i = 0; i < quantityOfEdge; i++)
    {
        vector<long> vec;
        long firstElement, secondElement;
        input >> firstElement ; 
        vec.push_back(firstElement);
        input >> secondElement;
        vec.push_back(secondElement);
        vectors.push_back(vec);
    }    
}

bool checkOneColorCodeExisted(vector<long> matching, long code){
    
    for (int i = 0; i < matching.size(); i++)
    {
        if (matching[i] == code)
        {
            return true;
        }       
    }
    return false;
}
long checkColorCode(vector<long> matching){
    long check = 1;
    for (int i = 0; i <= matching.size() + 1; i++)
    {
        if (!checkOneColorCodeExisted(matching,check))
        {
            return check;
        } else{
            check++;
        }
        
    }    
}

void print(fstream &output,long quantityOfEdges, long quantityOfTops, long colorCodes[] ){
    
    output << "graph dothi {\n";
    for (int i = 1; i <= quantityOfTops; i++)
    {

        output << i  << "[fillcolor=\"";
        output << colors[colorCodes[i]];
        output << "\", style=filled];"<< endl;  
    }
    
    for (int i = 0; i < quantityOfEdges; i++)
    {
        output << vectors[i][0] <<" -- "<< vectors[i][1]<<";" << endl;
    }
    
    output << "}";
}
#endif