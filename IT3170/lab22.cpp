#include<bits/stdc++.h>
using namespace std;
int n,k;
vector<bool> visited;
int dis[1000][1000];
int passenger;
int route[1000];
int min_route;
int cur_route;
int minDist;

int getMin(int a,int b){
    return (a<b)? a:b;
}
bool check( int toPoint){
    if(visited[toPoint]) return false;
    if(toPoint> n && visited[toPoint-n]== false) return false;
    if(toPoint <=n && passenger>=k) return false;
//    cout<< "ok";
    return true;
}
void checkSol(){
    cur_route += dis[route[2*n]][0];
    min_route= getMin(min_route,cur_route);
    cur_route -= dis[route[2*n]][0];
}

void findMin(){
    minDist = 2147483647;
    for(int i=0; i<=2*n; i++)
        for(int j=0; j<=2*n; j++){
            if(i!=j)
                minDist = getMin(minDist,dis[i][j]);
        }
    return;
}
void solve(int point){

    for(int i=1;i<2*n+1;i++){
        if(check(i)){
            route[point]=i;
            visited[i]=true;
            cur_route+= dis[route[point-1]][route[point]];
            if(i<=n){
                passenger++;
            } else passenger--;

            if(point==2*n){

                checkSol();
            }
            else if( cur_route +(2*n -point)*minDist <min_route) solve(point+1);


            if(i<=n){
                passenger--;
            } else passenger++;
            cur_route-= dis[route[point-1]][route[point]];
            visited[i]=false;
        }
    }

}

 int main(){

     cin>>n>>k;
     for(int i=0;i<2*n+1;i++){
        for(int j=0;j<2*n+1;j++){
            cin>> dis[i][j];
        }
     }
     visited.resize(2*n+1,false);

     min_route=9999;
     passenger=0;
     route[0]=0;
     visited[0]=true;
    findMin();
//    cout<< minDist;
     solve(1);

     //cout<< dis[0][1];
     cout<<min_route;

    return 0;
 }
