#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[10005], t[10005];
int dem = 0;
int cur =0;

void solve( int k)
{
    if( k== n+1)
    {
        if(cur == m) dem++;
        return;
    }
    for( int i=1; i<=m- cur -(t[n]-t[k])/a[k]; i++)
    {
        cur += a[k]*i;
        solve(k+1);
        cur -= a[k]*i;
    }
}
int main()
{
    cin>>n>>m;
    cin >> a[1];
    for( int i=2; i<=n; i++)
    {
        cin>> a[i];
        t[i]=t[i-1]+a[i];
    }
    solve(1);
    cout<< dem;

}
