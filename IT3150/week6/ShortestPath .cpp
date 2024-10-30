/*Given a directed graph G = (V,E) in which V = {1,2,...,n) is the set of nodes. Each arc (u,v) has a non-negative weight w(u,v). Given two nodes s and t of G. Find the shortest path from s to t on G.
Input
Line 1: contains two integers n and m which are the number of nodes and the number of arcs of G (1 <= n <= 100000)
Line i + 1(i = 1,2,...,m): contains 3 integers u, v, w in which w is the weight of arc(u,v) (0 <= w <= 100000)
Line m+2: contains two integers s and t
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

Output
97
*/
#include <iostream>
#include <vector>
#include <set>
using namespace std;
const long long infinite = 1e15, limit = 1e5 + 5;

vector<pair<long long, long long>> graph[limit];
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long quantityOfVertex, quantityOfEdges, dist[limit];
    cin >> quantityOfVertex >> quantityOfEdges;
    for (long long i = 1; i <= quantityOfEdges; i++)
    {
        long long firstVertex, secondVertex, distance;
        cin >> firstVertex >> secondVertex >> distance;
        graph[firstVertex].push_back(make_pair(secondVertex, distance));
    }
    long long begin, end;
    cin >> begin >> end;

    set<pair<long long, long long>> st;
    st.insert(make_pair(0, begin));

    for (long long i = 1; i <= quantityOfVertex; i++)
    {
        dist[i] = infinite;
    }
    dist[begin] = 0;

    while (!st.empty())
    {
        // pair<long long, long long> curVertex = *st.begin();
        long long vertex = st.begin()->second;
        st.erase(st.begin());
        if (vertex == end)
        {
            cout << dist[end];
            return 0;
        }


        for (auto &edge : graph[vertex])
        {
            long long next = edge.first, dis = edge.second;
            if (dist[next] > dist[vertex] + dis)
            {
                st.erase(make_pair(dist[next], next));
                dist[next] = dist[vertex] + dis;
                st.insert(make_pair(dist[next], next));
            }
        }
    }
    cout << (dist[end] == infinite ? -1 : dist[end]);
    return 0;
}
