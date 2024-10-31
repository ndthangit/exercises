/*Given a network G = (V, E) which is a directed weighted graph. Node s is the source and node t is the target. c(u,v) is the capacity of the arc (u,v). Find the maximum flow on G.
Input
•Line 1: two positive integers N and M (1 <= N <= 10
4
, 1 <= M <= 10
6
)
•Line 2: contains 2 positive integers s and t
•Line i+2 (I = 1,. . ., M): contains two positive integers u and v which are endpoints of i
th
 arc
Output
  Write the value of the max-flow found
Example
Input
7 12
6 7
1 7 7
2 3 6
2 5 6
3 1 6
3 7 11
4 1 7
4 2 4
4 5 5
5 1 4
5 3 4
6 2 8
6 4 10
Output
17*/

#include<bits/stdc++.h>
using namespace std;

const long long limit = 1e5 + 5;
vector<pair<long long, long long>> graph[limit];
vector<vector<long long>> allPaths;


long long *findElement(long long startNode, long long endNode)
{
    for (auto &element : graph[startNode])
    {
        if (element.first == endNode)
            return &element.second;
    }
    return nullptr;
}

void bfs(long long startNode, long long endNode, long long quantityOfVertex) {
    queue<vector<long long>> q;
    q.push({startNode});

    while (!q.empty()) {
        vector<long long> path = q.front();
        q.pop();

        long long node = path.back();

        if (node == endNode) {
            allPaths.push_back(path);
        }

        for (auto &edge : graph[node]) {
            long long nextNode = edge.first;
            vector<long long> newPath(path);
                newPath.push_back(nextNode);
                q.push(newPath);
        }

    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long quantityOfVertex, quantityOfEdges;
    cin >> quantityOfVertex >> quantityOfEdges;
    long long startNode, endNode;
    cin >> startNode >> endNode;
    startNode--;
    endNode--;

    for (long long i = 0; i < quantityOfEdges; i++) {
        long long firstVertex, secondVertex, distance;
        cin >> firstVertex >> secondVertex >> distance;
        graph[firstVertex - 1].emplace_back(secondVertex - 1, distance);
    }

    bfs(startNode, endNode, quantityOfVertex);

    long long maxFlow =0;
    for ( auto path : allPaths){
        long long add = *findElement(path[0], path[1]);
        for( long long i=1;i<path.size()-1;i++){
            add = min(add, *findElement(path[i], path[i+1]));
        }
        maxFlow+= add;
        for( long long i=0;i<path.size()-1;i++){
            *findElement(path[i], path[i+1]) -= add;
        }

    }
    cout<< maxFlow;

    return 0;
}


