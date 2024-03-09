#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
void setUpGraph(vector<vector<int>> graph, int quantityOfVertex, int quantityOfEdges)
{
    for (int i = 0; i < quantityOfEdges; i++)
    {
        int vertex1, vertex2, distance;
        cin >> vertex1 >> vertex2;
        graph[vertex1][vertex2] = distance;
        graph[vertex2][vertex1] = distance;
    }
}
void bfs(vector<vector<int>> graph, int start)
{
    vector<bool> visited(graph.size(), vector<bool>(graph.size(), false));
    queue<int> list;

    list.push(start);
    visited[start] = true;
    while (!list.empty())
    {
        int consideringVertex = list.front();

        list.pop();
        for (int i = 0; i < graph.size(); i++)
        {
            if (graph[consideringVertex][i] != 0 && visited[i] == false)
            {
                list.push(i);
                visited[i] = true;
            }
        }
    }
}
int main()
{
    int quantityOfVertex, quantityOfEdges;
    cin >> quantityOfVertex >> quantityOfEdges;
    vector<vector<int>> graph(quantityOfVertex, vector<int>(quantityOfVertex, 0));
    setUpGraph(graph, quantityOfVertex, quantityOfEdges);
    bfs(graph, 0);
    return 0;
}