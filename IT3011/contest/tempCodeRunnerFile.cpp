#include <iostream>
#include <vector>
#include <set>
using namespace std;
const long long infinite = 1e10 + 1, limit = 1e5 + 5;
long long quantityOfVertex, quantityOfEdges, begin, end, dist[limit];

vector<pair<long long, long long>> graph[limit];
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> quantityOfVertex >> quantityOfEdges;
    for (long long i = 1; i <= quantityOfEdges; i++)
    {
        long long firstVertex, secondVertex, distance;
        dist[i] = infinite;
        cin >> firstVertex >> secondVertex >> distance;
        graph[firstVertex].push_back(make_pair(secondVertex, distance));
    }
    cin >> begin >> end;

    set<pair<long long, long long>> st;
    st.insert(make_pair(begin, 0));
    dist[begin] = 0;

    while (!st.empty())
    {
        pair<long long, long long> curVertex = *st.begin();
        st.erase(st.begin());
        // if (st.begin()->first == end)
        // {
        //     cout << st.begin()->second;
        //     return 0;
        // }
        // else
        // {
        //     st.erase(st.begin());
        // }

        for (auto &edge : graph[curVertex.first])
        {
            if (dist[edge.first] > dist[curVertex.first] + edge.second)
            {
                st.erase(make_pair(edge.first, dist[edge.first]));
                dist[edge.first] = dist[curVertex.first] + edge.second;
                st.insert(make_pair(edge.first, dist[edge.first]));
            }
        }
    }
    cout << dist[end];
    return 0;
}