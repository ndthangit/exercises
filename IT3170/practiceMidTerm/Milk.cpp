#include<bits/stdc++.h>
using namespace std;
int n;
int a[50];
int m;
int dem =0;
int main()
{
    cin>>n;
    for( int i=0; i<n; i++) cin>> a[i];
    cin>>m;
    int total= 1<<n;
    for( int i=0; i<total; i++)
    {
        int sum=0;
        for( int j=0; j<n; j++)
        {
            if((1<<j)&i) sum += a[j];
        }
        if(sum>=m) dem++;
    }
    cout<< dem;

    return 0;
}
