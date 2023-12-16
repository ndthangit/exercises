#include<iostream>
using namespace std;

int bit[20];

void printArray(int bit[] ,int range){
    for (int i = 0; i < range; i++)
    {
        cout << bit[i];
    }
    cout << endl;
}

void backTracking(int k, int range){
    for (int  i = 0; i <= 1; i++)
    {
        bit[k] = i;
        if (k == range-1) printArray(bit,range);
        else backTracking(k+1, range);
    }
    
}

int main(){
    int range;
    cin >> range;
    backTracking(0,range);
}