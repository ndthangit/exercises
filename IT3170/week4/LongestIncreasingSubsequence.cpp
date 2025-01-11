#include<bits/stdc++.h>
using namespace std;
int n;
int a[100005];
int main()
{
    cin>> n;
    for( int i=1; i<=n; i++)
    {
        cin>> a[i];
    }
    vector<int > sp;
    for( int i =1; i<=n; i++)
    {
        auto res = lower_bound(sp.begin(), sp.end(),a[i]);
        if( res == sp.end())
        {
            sp.push_back(a[i]);
        }
        else
        {
            *res = a[i];
        }
    }
    cout<< sp.size();
}
