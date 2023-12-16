#include<iostream>
#include<algorithm>
#include<vector>
#include<ctime>
using namespace std;

vector<vector<long>> vectors;

void create(long quantityOfEdges){
    //tạo cây thông qua các cạnh
    for (int i = 0; i < quantityOfEdges; i++)
    {
        vector<long> vec;
        long firstElement, secondElement;
        cin >> firstElement >> secondElement; 
        vec.push_back(firstElement);
        vec.push_back(secondElement);
        vectors.push_back(vec);
    }    
}

void solution(long level[],long quantityOfEdges){
    // kiểm tra còn ít nhất 2 đỉnh có bậc khác 0
    long check;
    for ( check =1; check <= quantityOfEdges; check++){
        if (level[check] == 1) break;
    }

    bool next = false;
    for (int i = 1; i <= quantityOfEdges; i++)
    {
        if (level[i] > 0 && i != check)
        {
            next = true;
            break;
        }
        
    }
    //start 
    //các đỉnh bị xóa có bậc -1
    if (next)
    {
        long address = -1;
        for (int i = 0; i < vectors.size(); i++)
        {
            for (int j = 0; j < vectors[i].size(); j++)
            {
                if (vectors[i][j] == -1)
                {
                    break;
                }
                        
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
            
            }
            
        }
        vectors[address][0] = -1;
        level[check] = -1;
        solution( level,quantityOfEdges);
    }
    
}

int main (){
    long quantityOfEdges;
    cin >> quantityOfEdges;
    if (quantityOfEdges > 100000 || quantityOfEdges < 1)
    {
        return 0;
    }
    
    create(quantityOfEdges);

    //tạo một mảng bậc các phần tử
    long level[quantityOfEdges+1];
    for(int i=0; i<= quantityOfEdges;i++){
        level[i]=0;
    }
    for (int i = 0; i < quantityOfEdges; i++)
    {
        for (int j = 0; j < vectors[i].size(); j++)
        {
            level[vectors[i][j]]++;
        }
    }
    solution(level,quantityOfEdges);
    
    return 0;
}