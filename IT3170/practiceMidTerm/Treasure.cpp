#include<bits/stdc++.h>
using namespace std;
typedef struct Treasure
{
    long xi,yi,ci;
} Treasure;
long n;
vector<Treasure> dis;
long res[1100];
long best =0;

void solve()
{
    for( int i=0; i<n; i++)
    {
        res[i]= dis[i].ci;
    }
    for( int i=1; i<n; i++)
    {
        for(int j= i-1; j>=0; j--)
        {
            if( dis[i].xi>= dis[j].xi && dis[i].yi>= dis[j].yi) res[i] = max( res[i],res[j]+dis[i].ci);
        }
    }
    for(  int i=0 ; i<n; i++)
    {
        best = max( best, res[i]);
    }
    cout<< best;

}

int main()
{
    cin>> n;

    for(int i=0; i<n; i++)
    {
        Treasure a;
        cin>> a.xi>>a.yi>> a.ci;
        dis.push_back(a);
    }
    sort(dis.begin(),dis.end(),[]( const Treasure & a, const Treasure & b)
    {
        if( a.xi != b.xi) return a.xi<b.xi;
        else return a.yi < b.yi;
    });
    solve();

//    for( auto a : dis)  cout<< a.xi <<" "<<a.yi<< endl;

    return 0;
}
