#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
using namespace std;

void floyd(vector<vector<int>> &distance, int quantityVertex)
{
    //The Floyd Warshall algorithm is used to find all minimum paths between two random vertex in a small graph (the quantity of vertexes is lower than 400).
    for (int intermediatePoint = 0; intermediatePoint < quantityVertex; intermediatePoint++)
    {
        for (int begin = 0; begin < quantityVertex; begin++)
        {
            for (int end = 0; end < quantityVertex; end++)
            {
                if (begin != end)
                {
                    if (begin != intermediatePoint && end != intermediatePoint)
                    {
                        distance[begin][end] = min(distance[begin][end], distance[begin][intermediatePoint] + distance[intermediatePoint][end]);
                    }
                }
                else
                    distance[begin][end] = 0;
            }
        }
    }
}

void bfs(vector<vector<int>> &originalDistance, vector<vector<int>> &minDistance, int quantityVertex, int limitedDistance, int locationRobotA, int destinationA, int locationRobotB, int destinationB)
{
    //use bfs changed algorithm having a vertex as a edge( location A, location B) 
    vector<vector<bool>> visited(quantityVertex, vector<bool>(quantityVertex, false));
    queue<pair<int, int>> solve;
    stack<pair<int, int>> schedule;
    map<pair<int, int>, pair<int, int>> path;

    solve.push({locationRobotA, locationRobotB});
    visited[locationRobotA][locationRobotB] = true;

    cout << "location A | location B | distance 2 vertexes " << endl;

    while (!solve.empty())
    {
        pair<int, int> edge = solve.front();
        solve.pop();

        if (edge.first == destinationA && edge.second == destinationB)
        {
            pair<int, int> currentEdge = edge;
            while (currentEdge != make_pair(locationRobotA, locationRobotB))
            {
                schedule.push(currentEdge);
                currentEdge = path[currentEdge];
            }
            schedule.push(currentEdge);

            while (!schedule.empty())
            {
                pair<int, int> top = schedule.top();
                cout << "     " << top.first << "     |      " << top.second << "     |        " << minDistance[top.first][top.second] << endl;
                schedule.pop();
            }

            return;
        }

        // push in queue
        for (int nearlyEdge = 0; nearlyEdge < quantityVertex; nearlyEdge++)
        {
            if (visited[edge.first][nearlyEdge] == false && originalDistance[edge.second][nearlyEdge] != 10000 && nearlyEdge != edge.first && minDistance[edge.first][nearlyEdge] > limitedDistance)
            {
                visited[edge.first][nearlyEdge] = true;

                path[{edge.first, nearlyEdge}] = edge;
                solve.push({edge.first, nearlyEdge});
            }
        }
        for (int nearlyEdge = 0; nearlyEdge < quantityVertex; nearlyEdge++)
        {
            if (visited[nearlyEdge][edge.second] == false && originalDistance[nearlyEdge][edge.first] != 10000 && nearlyEdge != edge.second && minDistance[edge.second][nearlyEdge] > limitedDistance)
            {
                visited[nearlyEdge][edge.second] = true;

                path[{nearlyEdge, edge.second}] = edge;
                solve.push({nearlyEdge, edge.second});
            }
        }
    }
    cout << "khong the!" << endl;
}
int main()
{
    // set up graph
    int quantityVertex, quantityEdge;
    cin >> quantityVertex >> quantityEdge;
    vector<vector<int>> originalDistance(quantityVertex, vector<int>(quantityVertex, 10000));

    for (int i = 0; i < quantityEdge; i++)
    {
        int vertexX, vertexY;
        int distance2vertex;
        cin >> vertexX >> vertexY;
        cin >> distance2vertex;
        originalDistance[vertexX][vertexY] = distance2vertex;
        originalDistance[vertexY][vertexX] = distance2vertex;
    }
    // create minimum distance graph
    vector<vector<int>> minDistance = originalDistance;
    floyd(minDistance, quantityVertex);

    int locationRobotA, locationRobotB;
    int destinationA, destinationB;
    cin >> locationRobotA >> locationRobotB >> destinationA >> destinationB;

    int limitedDistance;
    cin >> limitedDistance;

    bfs(originalDistance, minDistance, quantityVertex, limitedDistance, locationRobotA, destinationA, locationRobotB, destinationB);
    return 0;
}
