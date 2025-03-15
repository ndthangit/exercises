#include <bits/stdc++.h>
using namespace std;
int n,m;
int a[1000];
int main(){
    cin>> n;
    for( int i=0;i<n;i++){
        cin>> a[i];
    }
    cin>> m;
    int total = 1<< n;
    int best = INT_MAX;
    for(int i=1;i<= total;i++){
        int sum=0;
        for(int j=0;j<n;j++){
            if( i & (1<<j)){
                sum += a[j];
            }
        }

        if( sum<=m){
            best = min(best, sum);
        }
    }
    cout<< best;
    return 0;
}