#include<bits/stdc++.h>
using namespace std;
long long n;
int const N= 1e6+5;
long long a[N],s[N], f[2];
long long res =INT_MIN;
int main()
{
    cin>>n;
    for( long long i=1; i<=n; i++)
    {
        cin>> a[i];
    }
    s[1]= a[1];
    for( long long i=2; i<=n; i++)
    {
        s[i]= s[i-1]+a[i];
    }
    f[0]=f[1]=0;
    for( long long i=1; i<=n; i++)
    {
        long long mod = abs(s[i])%2;
        if(i==1)
        {
            f[1]= s[i];
        }
        else
        {
            res= max(res, s[i]- f[mod]);
            f[mod]= min(f[mod], s[i]);
        }
        res= max(res, s[i]- f[mod]);
        f[mod]= min(f[mod], s[i]);
    }
    cout<< res;
}
