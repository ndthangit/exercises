/*

There are n passengers 1, 2, …, n. The passenger i want to travel from point i to point i + n (i = 1,2,…,n). There is a bus located at point 0 and has k places for transporting the passengers (it means at any time, there are at most k passengers on the bus). You are given the distance matrix c in which c(i,j) is the traveling distance from point i to point j (i, j = 0,1,…, 2n). Compute the shortest route for the bus, serving n passengers and coming back to point 0.
Input
Line 1 contains n and k (1≤n≤11,1≤k≤10)
 Line i+1 (i=1,2,…,2n+1) contains the (i−1)
th
 line of the matrix c (rows and columns are indexed from 0,1,2,..,2n).
Output
Unique line contains the length of the shortest route.
Example
Input
3  2
0  8  5  1  10  5  9
9  0  5  6  6  2  8
2  2  0  3  8  7  2
5  3  4  0  3  2  7
9  6  8  7  0  9  10
3  8  10  6  5  0  2
3  4  4  5  2  2  0
Output
25
*/
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

bool check( int point)
{
    if( visited[point]) return false;
    if(point >n && !visited[point-n]) return false;
    if( point<=n && cur_pass>=k) return false;
    return true;
}
void solve( int point)
{

    for( int i = 1; i<2*n+1; i++)
    {
        if(check(i))
        {

            route[point] =i;
            cur_route += dis[route[point-1]][i];
            if (i > n)
            {
                cur_pass--;
            }
            else
            {
                cur_pass++;
            }
            visited[i] = true;
            if( point == 2*n)
            {
                cur_route += dis[route[2*n]][0];
                best_route = min(best_route,cur_route);
                cur_route -= dis[route[2 * n]][0];
            }
            else if (cur_route +(2*n -point)* cmin <best_route)

            {
                solve(point+1);
            }

            visited[i] = false;
            if (i > n)
            {
                cur_pass++;
            }
            else
            {
                cur_pass--;
            }
            cur_route -= dis[route[point-1]][i];
        }
    }
}
int main()
{
    cin>> n>>k;
    visited.resize(2*n+1, false);
    route.resize(2*n+1,-1);
    visited[0]= true;
    for( int i =0; i< 2*n+1; i++)
    {
        for( int j=0; j< 2*n+1; j++)
        {
            cin>> dis[i][j];
            if (i!= j) cmin = min(cmin, dis[i][j]);
        }
    }
    route[0]=0;
    solve(1);

    cout<< best_route;
    return 0;
}
