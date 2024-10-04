/*
There are n passengers 1, 2, …, n. The passenger i want to travel from point i to point i + n (i = 1,2,…,n).
 There is a bus located at point 0 and has k places for transporting the passengers
  (it means at any time, there are at most k passengers on the bus).
  You are given the distance matrix c in which c(i,j) is the traveling distance from point i to point j (i, j = 0,1,…, 2n).
   Compute the shortest route for the bus, serving n passengers and coming back to point 0.
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

#include <bits/stdc++.h>
using namespace std;

vector<int> route;
vector<bool> visited;

int getMin(int a, int b) { return (a < b) ? a : b; }

bool check(int toPoint, int n, int k, int &passenger)
{
    if (toPoint <= n && passenger > k - 1)
        return false;
    if (toPoint > n ){
        if(visited[toPoint - n] == false)
            return false;
    }
    if(visited[toPoint]==true)
        return false;
    return true;
}

void solve(vector<vector<int>> &distance, int n, int &minRoute, int &curRoute, int pointTH, int k, int &passenger)
{
    cout << pointTH;
    if (pointTH == 2 * n + 1)
    {
        minRoute = getMin(minRoute, curRoute + distance[route[2 * n]][0]);
        return;
    }

    for (int i = 1; i < 2 * n + 1; i++)
    {
        if (check(i, n, k,passenger))
        {
            cout <<" to ";
            route[pointTH + 1] = i;
            visited[i] = true;
            if (i <= n)
                passenger++;
            else
                passenger--;

            curRoute += distance[route[pointTH - 1]][i];
            solve(distance, n, minRoute, curRoute, pointTH + 1, k, passenger);
            curRoute -= distance[route[pointTH - 1]][i];

            visited[i] = false;
            if (i <= n)
                passenger--;
            else
                passenger++;
            route[pointTH + 1] = -1;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    route.resize(2 * n + 1, -1);
    visited.resize(2 * n + 2, false);
    vector<vector<int>> distance(2 * n + 1, vector<int>(2 * n + 1));
    for (int i = 0; i <= 2 * n; i++)
    {
        for (int j = 0; j <= 2 * n; j++)
        {
            cin >> distance[i][j];
        }
    }
    int minRoute = INT_MAX;
    int curRoute = 0;
    route[0] = 0;
    visited[0] = true;
    int passenger = 0;

    // for (int i = 0; i < 2*n+1; i++)
    // {
    //     cout<< check(i, n, k,passenger) <<endl;    
    // }
    
    solve(distance, n, minRoute, curRoute, 0, k, passenger);
    cout << minRoute << endl;
    return 0;
}