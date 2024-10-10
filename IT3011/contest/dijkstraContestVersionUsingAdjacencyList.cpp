/*
Problem: Shortest Path between 2 nodes on a directed graph with non-negative weights
Description
Given a directed graph G = (V,E) in which V = {1,2,...,n) is the set of nodes. Each arc (u,v) has a non-negative weight w(u,v). Given two nodes s and t of G. Find the shortest path from s to t on G.
Input
Line 1: contains two intergers n and m which are the number of nodes and the number of arcs of G (1 <= n <= 100000)
Line i + 1(i = 1,2,...,m): contains 3 longegers u, v, w in which w is the weight of arc(u,v) (0 <= w <= 100000)
Line m+2: contains two longegers s and t
Output
Write the weight of the shortest path found or write -1 if no path from s to t was found
Example
Input
5 7
2 5 87
1 2 97
4 5 78
3 1 72
1 4 19
2 3 63
5 1 18
1 5
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Edge
{
    int nextVertex, distance;
};

void setUpGraph(vector<vector<Edge>> &graph, int quantityOfEdges)
{
    for (int i = 0; i < quantityOfEdges; i++)
    {
        int vertex1, vertex2, distance;
        cin >> vertex1 >> vertex2 >> distance;
        graph[vertex1].push_back({vertex2, distance});
    }
}

int minDistance(int dist[], bool visited[], int quantityOfVertex)
{
    int min = INT_MAX;
    int location;
    for (int i = 1; i <= quantityOfVertex; i++)
    {
        if (visited[i] == false && dist[i] <= min)
        {
            min = dist[i];
            location = i;
        }
    }
    return location;
}
void dijkstra(vector<vector<Edge>> &graph, int quantityOfVertex, int start, int end)
{
    int dist[quantityOfVertex + 1];
    bool visited[quantityOfVertex + 1];

    for (int i = 0; i <= quantityOfVertex; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[start] = 0;

    for (int j = 1; j <= quantityOfVertex - 1; j++)
    {
        int step = minDistance(dist, visited, quantityOfVertex);
        visited[step] = true;

        if (visited[end] == true)
        {
            cout << dist[end];
            return;
        }

        for (const auto &edge : graph[step])
        {
            if (!visited[edge.nextVertex] && dist[step] + edge.distance < dist[edge.nextVertex])
            {
                dist[edge.nextVertex] = dist[step] + edge.distance;
            }
        }
    }
}

void printTree(const vector<vector<Edge>> &graph, int quantityOfVertex)
{
    for (int i = 1; i <= quantityOfVertex; i++)
    {
        for (const auto &edge : graph[i])
        {
            cout << "vertex: " << i << " nextVertex: " << edge.nextVertex << " distance: " << edge.distance << endl;
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    
    int quantityOfVertex, quantityOfEdges;
    cin >> quantityOfVertex >> quantityOfEdges;
    // quantityOfVertex++;
    vector<vector<Edge>> graph(quantityOfVertex + 1);
    setUpGraph(graph, quantityOfEdges);
    // cout << graph.size();
    //  printTree(graph, quantityOfVertex);

    int start, end;
    cin >> start;
    cin >> end;
    dijkstra(graph, quantityOfVertex, start, end);

    return 0;
}
