#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include "coloring.h"

using namespace std;

int main(){
    long quantityOfEdges;
    long quantityOfTops; 

    fstream input("dothi.txt");
    fstream output;
    output.open("dothitomau.dot", ios :: out);
    
    input >> quantityOfTops;
    input >> quantityOfEdges;
    // tạo mảng lưu các đỉnh nối với nhau
    create(input,quantityOfEdges);

    vector<vector<long>> matching(quantityOfTops+1, vector<long>{});
    for (int i = 0; i < quantityOfEdges; i++)
    {
        matching[vectors[i][0]].push_back(vectors[i][1]);
        matching[vectors[i][1]].push_back(vectors[i][0]);
    }
    //tạo mảng lưu màu tô các đỉnh chưa tô lưu -1
    long colorCodes[quantityOfTops+1];
    for (int i = 0; i < quantityOfTops+1; i++)
    {
        if (i == 1)
        {
           colorCodes[i] = 1;
        } else colorCodes[i] = -1;        
    }
    /*
    ý tưởng tô màu có colorCodes là mã colorCodes bé nhất chưa xuất hiện trong dãy colorcodes của đỉnh cần tô và các đỉnh nối với nó
    */

    for (int i = 2; i <= quantityOfTops; i++)
    {
        colorCodes[i] = checkColorCode(matching[i]);
    }
 
    print(output, quantityOfEdges, quantityOfTops,colorCodes);
    input.close(); 
    output.close(); 
    return 0;
}