#include <bits/stdc++.h>
using namespace std;
const long long mod = 1e9+7;

long long arr[1001][1001];

long long c_k_n(int k, int n){
    if (k == 0 || k == n){
        arr[k][n] = 1;
    }
    else if (k == 1)
    {
        arr[k][n] = n;
    }
    else if (arr[k][n] == -1)
    {
        arr[k][n] = (c_k_n(k-1,n-1) + c_k_n(k,n-1)) % mod;
    }
    return arr[k][n];
    
    
}
int main(){
    for (int i = 0; i < 1001; i++)
    {
        for (int j = 0; j < 1001; j++)
        {
            arr[i][j]=-1;
        }
        
    }
    
    int k,n;
    cin>> k >> n;
    cout<< c_k_n(k,n);
    return 0;
}