/*
Given undirected graph G = (V,E) in which V = {1, 2, ..., n} is the set of nodes, and E is the set of m edges.
Write a program that computes the sequence of nodes visited using a BFS algorithm (the nodes are considered in a lexicographic order)

Input
Line 1: contains 2 integers n and m which are the number of nodes and the number of edges
Line i+1 (i = 1, ..., m): contains 2 positive integers u and v which are the end points of the ith edge

Output
Write the sequence of nodes visited by a BFS procedure (nodes a are separated by a SPACE character)
Example

Input
6 7
2 4
1 3
3 4
5 6
1 2
3 5
2 3

Output
1 2 3 4 5 6
*/
#include<bits/stdc++.h>
using namespace std;

int n,m;
vector<pair<int,int>> edge;
vector<bool> visited;
//set<int> a;
queue<int> q;
void BFS()
{
    while(!q.empty())
    {
        int b= q.front();
        q.pop();
        cout<< b<<" ";
        set<int> a;
        for( int i=0; i<m; i++)
        {
            if(edge[i].first== b && visited[edge[i].second]==false)
            {
//            q.push(edge[i].second);
                visited[edge[i].second]=true;
                a.insert(edge[i].second);
            }
            else if(edge[i].second== b && visited[edge[i].first]==false)
            {
//            q.push(edge[i].first);
                visited[edge[i].first]=true;
                a.insert(edge[i].first);
            }

        }
        for(auto i : a)
        {
            q.push(i);

        }


    }
}

int main()
{
    cin>> n>>m;
    edge.resize(m);
    visited.resize(n+1, false);
    for(int i=0; i<m; i++)
    {
        cin>>edge[i].first>>edge[i].second;
    }
    visited[0]= true;
    for( int i=1;i<=n;i++){
        if(!visited[i]){
            q.push(i);
            visited[i]= true;
            BFS();
        }
    }

    return 0;
}
