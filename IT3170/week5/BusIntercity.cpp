#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n,m;
int c[N], d[N];
vector<int> graph[N];


int main()
{
    cin>> n>> m;
    for( int i=1; i<=n; i++)
    {
        cin>> c[i]>> d[i];
    }
    for( int i=1; i<=m; i++)
    {
        int a,b;
        cin>> a>> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<bool> visited(n+1, false);
    vector<int> cost(n+1, INT_MAX);
    cost[1]=0;


    priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0,1});

    while(!pq.empty())
    {
        pair<int, int> cur= pq.top();
        int cur_cost = cur.first;
        int cur_point = cur.second;

        pq.pop();
        if(cost[cur_point]<cur_cost) continue;
        if( cur_point== n)
        {
            cout<< cur_cost;
            return 0;
        }
        if( !visited[cur_point])
        {
            visited[cur_point] = true;
            int step = d[cur_point];
            queue<int> q;
            q.push(cur_point);

            vector<int> pointStep(n+1, -1);
            pointStep[cur_point]=0;

            while(!q.empty())
            {
                int a = q.front();

                q.pop();

                if(pointStep[a]== step) continue;

                for( auto &point : graph[a])
                {
                    if(pointStep[point] ==-1)
                    {
                        pointStep[point] = pointStep[a] +1;
                        if(pointStep[point] <= step) q.push(point);
                    }

                }

            }
            for(int i=1; i<=n; i++)
            {
                if(pointStep[i] !=-1 && i != cur_point)
                {
                    int new_cost = cur_cost + c[cur_point];
                    if( new_cost< cost[i])
                    {
                        cost[i]= new_cost;
                        pq.push({new_cost,i});
                    }
                }
            }

        }


    }
    cout<< -1;

    return 0;


}
