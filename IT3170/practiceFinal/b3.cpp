#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[1005];
int main(){
    cin>> n;
    for( int i=0;i<n;i++){
        cin>> a[i];
    }
    cin>> m;
    int loop = 1<<n;
    int best= INT_MAX;
    for( int i=1;i<=loop;i++){
        int sum=0;
        for(int j=0;j<n;j++){
            if((1<<j) & i){
                sum += a[j];
            }
        }
        if( sum <=m){
            best= min( best, m - sum);
        }
    }
    cout<< best;
}
