#include<bits/stdc++.h>
using namespace std;
int num_trucks, capacity, num_clients, disMin= INT_MAX, dis0Min = INT_MAX;
vector<int> request;
vector<bool> visited;

int dis[50][50];
int routeOfVehicle[7][15];

int Kth_truck,num_clients_kth_truck,num_visited=0;
int minRoute=INT_MAX;
int curRoute=0;

int predict(){
    int total_remain_request=0;
    int test = (num_clients-num_visited)*disMin;
    for(int i=1;i<= num_clients;i++){
        if(!visited[i]) total_remain_request+= request[i];
    }
    for( int truck =1;truck<= num_trucks;truck++){
        int point = -1;
        int disKth= dis[0][routeOfVehicle[truck][0]];
        int request_kth =0;
        while(routeOfVehicle[truck][++point]){
            disKth += dis[routeOfVehicle[truck][point]][routeOfVehicle[truck][point+1]];
            request_kth += request[routeOfVehicle[truck][point]];
        }
        if(truck >= Kth_truck){
            disKth += dis0Min - dis[routeOfVehicle[truck][point-1]][0];
            total_remain_request+= request_kth%capacity;
        }
        test += disKth * ((request_kth+ capacity-1)/capacity);
    }
    if(total_remain_request> capacity* (num_trucks+1- Kth_truck)) test+= 2* dis0Min+ disMin;
    return test;
}

void solve(){
    if (num_visited==num_clients){
        int test =0;
        for( int truck =1;truck<= num_trucks;truck++){
            int point = -1;
            int disKth= dis[0][routeOfVehicle[truck][0]];
            int request_kth =0;
            while(routeOfVehicle[truck][++point]){
                disKth += dis[routeOfVehicle[truck][point]][routeOfVehicle[truck][point+1]];
                request_kth += request[routeOfVehicle[truck][point]];

            }

            test += disKth * ((request_kth+ capacity-1)/capacity);
        }
        minRoute= min(minRoute,test);
        return;
    }
    if(Kth_truck< num_trucks){
        int tmp = num_clients_kth_truck;
        Kth_truck++;
        num_clients_kth_truck=1;
        solve();
        Kth_truck--;
        num_clients_kth_truck= tmp;
    }
    for(int client=1; client<= num_clients;client++){
        if(!visited[client]){
            routeOfVehicle[Kth_truck][num_clients_kth_truck++]=client;
            num_visited++;
            visited[client]=true;

            if(predict()< minRoute) solve();

            visited[client]= false;
            num_visited--;
            routeOfVehicle[Kth_truck][--num_clients_kth_truck]=0;
        }
    }
}
void try_vehicle(int vehicle){
    if( vehicle> num_trucks){
        num_visited= num_trucks;
        Kth_truck=1;
        num_clients_kth_truck=1;
        solve();
        return;
    }
    for( int i = routeOfVehicle[vehicle-1][0]+1;i<= num_clients;i++){
        routeOfVehicle[vehicle][0]=i;
        visited[i]= true;
        try_vehicle(vehicle+1);
        visited[i]=false;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>> num_clients>> num_trucks >> capacity;

    request.resize(num_clients+1);
    visited.resize(num_clients+1, false);

    for (int i=1; i<= num_clients;i++) {
        cin>> request[i];
    }
    for(int i=0;i<= num_clients;i++){

        for(int j=0;j<= num_clients;j++){
           cin>> dis[i][j];
           if(dis[i][j]>0 &&dis[i][j]<disMin) disMin = dis[i][j];
        }
    }
    for (int i=1; i<= num_clients;i++) {
        dis0Min = min(dis0Min, dis[i][0]);
    }
//    cout<< disMin;
    int start =num_trucks+1;
    visited[0]= true;
    while(--start){
        try_vehicle(start);
    }
    cout<< minRoute;
    return 0;
}
