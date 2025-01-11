#include<bits/stdc++.h>
using namespace std;
int T;
int a[100020];
int N,C;

bool check(int mid)
{
    int l=0;
    int r=1;
    int dem =1;
    for(; r<N; r++)
    {
        if(a[r]-a[l]>= mid)
        {
            dem++;
            l=r;
        }
    }
    return dem >= C;
}
int solve()
{
    int l =0;
    int r = a[N-1]-a[0];

    while(l<r)
    {
        int mid =(l+r+1)/2;
        if( check(mid))
        {
            l= mid;
        }
        else
        {

            r= mid -1;
        }
    }
    return l;

}
int main()
{
    cin>> T;
    for(int i=0; i<T; i++)
    {
        cin>>N>>C;
        for( int j=0; j<N; j++)
        {
            cin>> a[j];
        }
        sort(a,a+N);
        cout<< solve()<< endl;
    }
    return 0;
}
