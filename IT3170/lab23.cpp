#include<bits/stdc++.h>
using namespace std;
int m,n; // m teachers, n coureses

bool conf[100][100];
bool tech[100][100];


void solution(){

}
int main(){

    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            conf[i][j] =false;
            tech[i][j] =false;
        }
    }
    cin>> m >>n;
    for(int i=0;i<m;i++){
        int num;
        cin>>num;
        for(int j=0;j<num;j++){
            int a;
            cin>>a;
            tech[i][a] = true;
        }
    }
    int k;
    cin>> k;
    for(int i=0;i<k;i++){
        int a,b;
        cin>>a>>b;
        conf[a][b]= true;
        conf[b][a] = true;
    }

    return 0;
}
