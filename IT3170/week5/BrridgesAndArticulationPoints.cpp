#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n,m,cnt=0;
int articulation =0;
int bridges  =0;
int low[N], num[N];
vector<int> ds[N];
bool isArticulation[N];

void solve( int point, int parent)
{
    low[point] = num[point] = ++cnt;

    int child=0;

    for( auto v : ds[point])
    {
        if( v != parent)
        {
            if(num[v])
            {
                low[point] = min(low[point], num[v]);
            }
            else
            {
                solve(v,point);
                child++;
                low[point]= min(low[point],low[v]);

                if (low[v] > num[point]) bridges++;

                if (parent == point)
                {
                    if (child > 1) isArticulation[point] = true;
                }
                else
                {
                    if (low[v] >= num[point]) isArticulation[point] = true;
                }

            }
        }

    }

}



int main()
{
    cin>> n>>m;
    memset(low,0,sizeof(low));
    memset(num,0,sizeof(num));
    memset(isArticulation,false,sizeof(isArticulation));


    for( int i=0; i<m; i++)
    {
        int a,b;
        cin>>a>>b;
        ds[a].push_back(b);
        ds[b].push_back(a);
    }

    for (int i = 1; i <= n; i++)
    {
        if (!num[i]) solve(i, i);
    }

    for (int i = 1; i <= n; i++)
    {
        if (isArticulation[i]) articulation++;
    }

    cout<< articulation<<" " << bridges ;

}
