#include<iostream>
using namespace std;

long prufer;
long checkLevel(long tree[],long range){
    long rank = 0;
    for (int i = 0; i <= range; i++)
    {
        if(tree[i] ==1){
            prufer = i;
            rank += tree[i];
        } 
    }   
    return rank;
}
int main(){
    long quantityOfEdges;
    
    //create a tree
    cin >> quantityOfEdges;
    long tree[quantityOfEdges+1][quantityOfEdges+1] ;
    for (int i = 0; i <= quantityOfEdges; i++)
    {
        for (int j = 0; j <= quantityOfEdges; j++)
        {
           tree[i][j] = 0;
        }
    }

    for (int i = 1; i <= quantityOfEdges; i++)
    {
        long firstElement, secondElement;
        
        cin >> firstElement ;
        cin >> secondElement;
        tree[firstElement][secondElement] =1;
        tree[secondElement][firstElement] =1;
    }

    for (int i = 1; i < quantityOfEdges; i++)
    {
        for (int j = 1; j <= quantityOfEdges; j++)
        {
            if (checkLevel(tree[j],quantityOfEdges) == 1)
            {
                cout<< prufer<<" ";
                tree[prufer][j] = 0;
                tree[j][prufer] = 0;
                break;
            }
        }                       
    }
    
 }