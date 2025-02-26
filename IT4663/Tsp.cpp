#include<bits/stdc++.h>
using namespace std;
int n,k;
const int N = 1e3;
int dis[N][N];
vector< bool> visited;
vector<int> route;
int cmin = INT_MAX;
int best_route = INT_MAX;
int cur_route =0;
int cur_pass=0;
int route_test[1000];

bool check( int point)
{
    if( visited[point]) return false;
    return true;
}

void solve( int point)
{

    for( int i = 1; i<n; i++)
    {
        if(check(i))
        {

            route[point] =i;
            cur_route += dis[route[point-1]][i];
           
            visited[i] = true;
            if( point == n-1)
            {
                cur_route += dis[route[n-1]][0];
                best_route = min(best_route,cur_route);
                cur_route -= dis[route[n-1]][0];
            }
            else if( cur_route + (n-point)*cmin < best_route)
            {
                solve(point+1);
            }

            visited[i] = false;
            cur_route -= dis[route[point-1]][i];
        }
    }
}
int main()
{
    cin>> n;
    visited.resize(n, false);
    route.resize(n,-1);
    visited[0]= true;

    for( int i =0; i< n; i++)
    {
        for( int j=0; j< n; j++)
        {
            cin>> dis[i][j];
            if (i!= j) cmin = min(cmin, dis[i][j]);
        }
    }
    route[0]=0;
    visited[0]= true;
    solve(1);

    cout<< best_route;
    return 0;
}