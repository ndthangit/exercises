/*
A fleet of K identical trucks having capacity Q need to be scheduled to delivery pepsi packages
from a central depot 0 to clients 1,2,…,n. Each client i requests d[i] packages.
The distance from location i to location j is c[i,j], 0≤i,j≤n. A delivery solution is a set of routes:
 each truck is associated with a route, starting from depot, visiting some clients and returning to the depot for
 deliverying requested pepsi packages such that:
Each client is visited exactly by one route
Total number of packages requested by clients of each truck cannot exceed its capacity
Goal
Find a solution having minimal total travel distance
Note that:
There might be the case that a truck does not visit any client (empty route)
The orders of clients in a route is important, e.g., routes 0 -> 1 -> 2 -> 3 -> 0 and 0 -> 3-> 2 -> 1 -> 0 are different.
Input
Line 1: n,K,Q (2≤n≤12,1≤K≤5,1≤Q≤50)
Line 2: d[1],...,d[n](1≤d[i]≤10)
Line i+3 (i=0,…,n): the i
th
 row of the distance matrix c (1≤c[i,j]≤30)
Output
Minimal total travel distance
Example
Input
4 2 15
7 7 11 2
0 12 12 11 14
14 0 11 14 14
14 10 0 11 12
10 14 12 0 13
10 13 14 11 0

Output
70
*/
#include<bits/stdc++.h>
using namespace std;

int num_trucks, capacity, num_clients, disMin, num_visited,nbr;
vector<int> request;
vector<int> firstPoint, nextPoint;
vector<bool> visited;
vector<int> curCapacity;
vector<int> curRouteVehicle;
int dis[50][50];

int minRoute;
int curRoute;

bool check_nextPoint(int nextClient, int vehicle){
    if(nextClient>0 && visited[nextClient]) return false;
    if(curCapacity[vehicle]+request[nextClient]> capacity) return false;
    return true;
}
void try_schedule(int point ,int vehicle){
    if(point==0){
        if(vehicle< num_trucks)
            try_schedule(firstPoint[vehicle+1], vehicle+1);
        return;
    }
    for(int next =0; next<=num_clients;next++){
        if(check_nextPoint(next, vehicle)){
            visited[next]=true;
            nextPoint[vehicle]= next;
            curRoute += dis[point][next];
            curCapacity[vehicle] += request[next];
            num_visited++;

            if(next>0){
                int predict = curRoute +( num_clients+nbr - num_visited)*disMin;
                if(predict<minRoute) try_schedule(next, vehicle);

            } else {
                if(vehicle == num_trucks){
                    if((num_clients+nbr)==num_visited){
                         minRoute = min(minRoute,curRoute);
                    }
                } else {
                   int predict = curRoute +( num_clients+nbr - num_visited)*disMin;
                    if(predict<minRoute) try_schedule(firstPoint[vehicle+1], vehicle+1);
                }
            }
            visited[next]= false;
            curRoute -= dis[point][next];
            curCapacity[vehicle] -= request[next];
            num_visited--;
        }
    }
}
bool check_firstPoint(int point, int vehicle){
    if(point == 0) return true;
    if(visited[point]) return false;
    if(curCapacity[vehicle]+ request[point]> capacity) return false;
    return true;
}

void try_firstPoint(int vehicle){
    int s=0;
    if(firstPoint[vehicle-1]>0) s= firstPoint[vehicle-1] +1;
    for(int client= s;client<= num_clients; client++){
        if(check_firstPoint(client, vehicle)){
            firstPoint[vehicle]= client;
            if(client>0) num_visited++;
            visited[client]= true;
            curRoute+= dis[0][client];
            curCapacity[vehicle]+= request[client];

            if(vehicle< num_trucks) try_firstPoint(vehicle+1);
            else{
                nbr = num_visited;
                try_schedule(firstPoint[1],1);
            }
            if(client>0) num_visited--;
            visited[client]=false;
            curRoute -= dis[0][client];
            curCapacity[vehicle]-= request[client];
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>> num_clients>>num_trucks>> capacity;
    request.resize(num_clients+1);
    visited.resize(num_clients+1, false);
    firstPoint.resize(num_trucks+1,0);
    nextPoint.resize(num_trucks+1,0);
    curCapacity.resize(num_trucks+1,0);
    curRouteVehicle.resize(num_trucks+1,0);
    num_visited=0;
    minRoute=INT_MAX;
    curRoute=0;
    disMin=INT_MAX;
    firstPoint[0]=0;

    for (int i=1; i<= num_clients;i++) {
        cin>> request[i];
    }
    for(int i=0;i<= num_clients;i++){
        for(int j=0;j<= num_clients;j++){
           cin>> dis[i][j];
           if(dis[i][j]>0 &&dis[i][j]<disMin) disMin = dis[i][j];
        }
    }
//    cout<< disMin;
    try_firstPoint(1);

    cout<< minRoute;

    return 0;
}
