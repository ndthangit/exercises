#include<bits/stdc++.h>
using namespace std;
int N,T,D;
struct point
{
    int a,t;
};
point lisPoinnt[10000];
int f[10000][10000];
int res= INT_MIN;
int main()
{
    cin>>N>>T>>D;
    for ( int i=1; i<=N; i++)
    {
        cin>> lisPoinnt[i].a;
    }
    for ( int i=1; i<=N; i++)
    {
        cin>> lisPoinnt[i].t;
    }
    memset(f,0,sizeof(f));
    for( int i=1; i<=N; i++)
    {
        for(int k =lisPoinnt[i].t; k<=T; k++)
        {
            for ( int j=max(0, i-D); j<i; j++)
            {
                f[i][k]= max(f[i][k], f[j][k- lisPoinnt[i].t]+lisPoinnt[i].a);
            }
        }
    }

    for( int i=1; i<=N; i++)
    {
        for(int k =1; k<=T; k++)
        {
            res = max(res,f[i][k]);
        }
    }
    cout<< res;


    return 0;
}
