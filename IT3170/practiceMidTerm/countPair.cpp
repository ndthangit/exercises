#include<bits/stdc++.h>
using namespace std;
long n;
long a[100001];
long res[100001];
map< long, long> feq;
long sum =0;

int main(){
    cin>> n;
    memset(res, 0,sizeof(res));
    for( int i=1;i<= n;i++){
        cin>> a[i];
        res[i]= feq[a[i]];
        feq[a[i]]++;
    }
//    for(int i=1;i<=n;i++) cout<< res[i]<<" ";
    for(int i=1;i<=n;i++) sum += res[i];
    cout<< sum;


    return 0;
}
