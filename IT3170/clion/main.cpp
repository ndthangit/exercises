#include <bits/stdc++.h>
using namespace std;

vector<int> route;
vector<bool> visited;

int getMin( int a, int b) { return (a < b) ? a : b; }

bool check(int toPoint, int n, int k, int passenger)
{
    if (toPoint <= n && passenger >= k) // If picking up a passenger exceeds capacity
        return false;

    if (toPoint > n && !visited[toPoint - n]) // If dropping off at a non-visited point
        return false;

    if (visited[toPoint]) // If already visited this point
        return false;

    return true;
}

void solve(vector<vector<int>> &distance, int n, int &minRoute, int &curRoute, int pointTH, int k, int &passenger)
{
    if (pointTH == 2 * n) // Base case: all passengers picked up and returned
    {
        minRoute = getMin(minRoute, curRoute + distance[route[pointTH - 1]][0]);
        return;
    }

    for (int i = 1; i <= 2 * n; i++)
    {
        if (check(i, n, k, passenger))
        {
            route[pointTH] = i; // Correct index used

            visited[i] = true;
            if (i <= n)
                passenger++; // pickup
            else
                passenger--; // dropoff

            curRoute += distance[route[pointTH - 1]][i]; // Update current route distance
            solve(distance, n, minRoute, curRoute, pointTH + 1, k, passenger);
            curRoute -= distance[route[pointTH - 1]][i]; // Backtrack

            visited[i] = false; // Unmark this node
            if (i <= n)
                passenger--; // backtrack pickup
            else
                passenger++; // backtrack dropoff
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    route.resize(2 * n, -1);
    visited.resize(2 * n + 1, false); // Only need 2*n + 1 elements for visited
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
    route[0] = 0; // Starting point (Assuming driver starts from point 0)
    visited[0] = true;
    int passenger = 0;

    solve(distance, n, minRoute, curRoute, 0, k, passenger);

    cout << minRoute << endl;
    return 0;
}
