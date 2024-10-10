/*
There are two jugs, a-litres jug and b-litres jug (a, b are positive integers). There is a pump with unlimited water.
Given a positive integer c, how to get exactly c litres.
Input
   Line 1: contains positive integers a,   b,  c  (1 <= a, b, c <= 900)
Output
  write the number of steps or write -1 (if no solution found)
Example

Input
6  8  4
Output
4
*/
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int, int>

map <pii, int> level;
queue<pii> q;

void Pour(int a, int b, pii u){
    if(level.find({a, b}) == level.end()){
        q.push({a,b});
        level[{a,b}] = level[u] + 1;
    }
}

void bfs(int a, int b, int target){
    bool SOLVED = false;
    q.push({0,0});
    level[{0,0}] = 0;
    while (!q.empty()){
        pii u = q.front();
        q.pop();
        if(u.first== target|| u.second== target){
            SOLVED = true;
            cout<< level[u];
            return;
        }
        Pour(0, u.second,u);
        Pour(u.first,0,u);
        Pour(a,u.second,u);
        Pour(u.first,b,u);

        int pourA = min(u.first, b - u.second);
        Pour(u.first - pourA, u.second + pourA, u);

        int pourB = min(u.second, a - u.first);
        Pour(u.first + pourB, u.second - pourB, u);

    }
    if(!SOLVED){
        cout<<-1;
        return;
    }

}

int main(){
    int a,b,c;
    cin>>a>>b>>c;
    bfs(a,b,c);
    return 0;
}
