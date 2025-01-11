#include<bits/stdc++.h>
using namespace std;
int n,k1,k2;
int f[10000][2];
const int mod = 1e9+7;
int main(){
    cin>>n>>k1>>k2;
    f[0][0]=f[0][1]=1;
    for(int i=1;i<=n;i++){
        f[i][0]= f[i-1][1];
        f[i][1]=0;
        for( int j=k1;j<=k2;j++){
            if( i>=j) f[i][1] =(f[i][1]+ f[i-j][0])%mod;
        }
    }
    cout<< f[n][0]+f[n][1];
    return 0;
}
