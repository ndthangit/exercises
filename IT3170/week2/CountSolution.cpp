#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[10000];
int t[10000];
int cur;
int dem;

void try1(int k)
{
    if( k== n+1){
        if (cur == m) dem++;
        return;
    }
    for( int i=1; i<= m - cur -(t[n]- t[k])/a[k]; i++)
    {
        cur += a[k]*i;
        try1(k+1);
        cur -= a[k]*i;
    }

}
int main()
{
    cin>>n>>m;
    cin>> a[1];
    t[1]= a[1];
    for( int i=2; i<= n; i++)
    {
        cin>> a[i];
        t[i]= t[i-1]+a[i];

    }
    dem=0;
    cur =0;
    try1(1);
    cout<< dem;
    return 0;
}
