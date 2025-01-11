#include<bits/stdc++.h>
using namespace std;
int n;
const int N = 1e7;
int a[N];
int res[N];
const int mod = 1e9+7;

int main(){
    cin>>n;
    for( int i=1;i<=n;i++){
        cin>> a[i];
    }
    res[n]=0;
    for(int i=n-1;i>0;i--){
        res[i]= res[find(a+i+1,a+n,>a[i])]+1;;
    }
    long sum=0;
    for( int i=1;i<=n;i++){
        sum = (sum+ res[i])% mod;
    }
    cout<< sum;
}
