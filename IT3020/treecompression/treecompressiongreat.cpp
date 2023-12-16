#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

vector<vector<long>> vectors;

void create(long quantityOfEdge){
    //create a tree through edges
    for (int i = 0; i < quantityOfEdge; i++)
    {
        vector<long> vec;
        long firstElement, secondElement;
        cin >> firstElement >> secondElement; 
        vec.push_back(firstElement);
        vec.push_back(secondElement);
        vectors.push_back(vec);
    }    
}

void solution(long level[],long quantityOfEdge){
    long check;
    for ( check =1; check <= quantityOfEdge; check++){
        if (level[check] == 1) break;
    }
    if (check > quantityOfEdge )
    {
        return;
    }
    bool next = false;
    for (int i = check+1; i <= quantityOfEdge; i++)
    {
        if (level[i] == 1)
        {
            next = true;
            break;
        }
        
    }
    
    long address = -1;
    for (int i = 0; i < vectors.size(); i++)
    {
        for (int j = 0; j < vectors[i].size(); j++)
        {
            if (vectors[i][j] == check)
            {
                address = i;
                break;
            }           
        }
        if (address != -1)
        {
            break;
        } 
        
    }
    
    for (int j = 0; j < 2; j++)
    {
        if (vectors[address][j] != check)
        {
            level[vectors[address][j]]--;
            cout << vectors[address][j] <<" ";
            vectors[address][j] = -1;
        }
        
    }
    
    level[check] = -1;
    //cout<< "vector:"<< address <<endl;//
    solution( level,quantityOfEdge);
}

int main (){
    long quantityOfEdge;
    cin >> quantityOfEdge;
    create(quantityOfEdge);

    //create a level list of elements
    long level[quantityOfEdge+1];
    for(int i=0; i<= quantityOfEdge;i++){
        level[i]=0;
    }
    for (int i = 0; i < quantityOfEdge; i++)
    {
        for (int j = 0; j < vectors[i].size(); j++)
        {
            level[vectors[i][j]]++;
        }
    }
    solution(level,quantityOfEdge);
    
    
    return 0;
}