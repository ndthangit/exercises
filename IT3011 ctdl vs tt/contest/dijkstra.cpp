#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
void setUpGraph(vector<vector<int>> graph, int quantityOfVertex, int quantityOfEdges)
{
    for (int i = 0; i < graph.size(); i++)
    {
        graph[i][i] = 0;
    }

    for (int i = 0; i < quantityOfEdges; i++)
    {
        int vertex1, vertex2, distance;
        cin >> vertex1 >> vertex2;
        graph[vertex1][vertex2] = distance;
        graph[vertex2][vertex1] = distance;
    }
}
int minDistance(vector<int> dist, bool chose[])
{
    int min = INT16_MAX;
    for (int i = 0; i < dist.size(); i++)
    {
        if (choose[i] == false && dist[i] < min)
        {
            min = 
        }
    }
}
int main()
{
    int quantityOfVertex, quantityOfEdges;
    cin >> quantityOfVertex >> quantityOfEdges;
    vector<vector<int>> graph(quantityOfVertex, vector<int>(quantityOfVertex, -1));
    setUpGraph(graph, quantityOfVertex, quantityOfEdges);

    return 0;
}