/*
Given a undirected graph =(V,E) in which V = {1,2,..,n} is the set of nodes.
Write a program that visit nodes of G by a DFS (consider a lexicorgraphic order of nodes).
Input
Line 1: contains 2 integers n and m (1 <= n,m <= 100000)
Line i+1: contains u and v which are two end-points of the ith edge

Output
Sequence of nodes visited by DFS
Example
Input
7 12
1 2
1 3
2 3
2 4
2 7
3 5
3 7
4 5
4 6
4 7
5 6
5 7
Output
1 2 3 5 4 6 7
*/
#include<bits/stdc++.h>
using namespace std;

int n,m;
vector<pair<int,int>> edge;
vector<bool> visited;
void DFS( int point){
    visited[point]= true;
    cout<< point<<" ";

    for( int i=0; i<m;i++){
        if(edge[i].first== point && visited[edge[i].second]==false){
            point = edge[i].second;
            DFS(point);
        } else if(edge[i].second== point && visited[edge[i].first]==false){
            point = edge[i].first;
            DFS(point);
        }
    }
}

int main(){
    cin>> n>>m;
    edge.resize(m);
    visited.resize(n+1, false);
    for(int i=0;i<m;i++){
        cin>>edge[i].first>>edge[i].second;
    }
    visited[0]= true;
    DFS(1);
    return 0;
}
