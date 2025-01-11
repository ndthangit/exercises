#include<bits/stdc++.h>
using namespace std;
int n,k,q,m,cmin=INT_MAX;
int best= INT_MAX;

int c[15][15];

int route[10][15];
bool visied[15], conf[15][15];

void try_vehicle( int vehicle ){
    if(vehicle==k){

    }

}

int main(){
    cin>>n>>k>>q;
    for( int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            cin>> c[i][j];
            cmin = min( cmin, c[i][j]);
        }
    }
    memset(visied,false,sizeof(visied));
    memset(conf,false,sizeof(conf));
    memset(route,0,sizeof(route));
    cin>> m;
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        conf[a][b]= true;
        conf[b][a]= true;
    }
    try_vehicle(1);
    cout<< best;
    return 0;
}
