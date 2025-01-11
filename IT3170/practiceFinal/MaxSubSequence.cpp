#include<bits/stdc++.h>
using namespace std;
int n;
const int N= 1e6+2;
int a[N];
int main(){
    memset(a,0, sizeof(a));
    cin>> n;
    for( int i=1;i<=n;i++){
        cin>> a[i];
    }


    int maxSum= a[1];
    int curMax = a[1];
    for( int i=2;i<=n;i++){
        curMax = max( a[i], curMax+a[i]);
        maxSum= max( maxSum, curMax);
    }
    cout<< maxSum;
}
