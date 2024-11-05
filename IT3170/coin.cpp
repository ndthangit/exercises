#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int N = 20;
const int XMAX = 1e5 + 5;
int D[N], mem[N][XMAX];


int MinCoin(int i, int x)
{
    if (x < 0 || i == 0) return INF;
    if (x == 0) return 0;
    if (mem[i][x] != -1) return mem[i][x];
    int res = INF;
    res = min(res, 1 + MinCoin(i, x - D[i]));
    res = min(res, MinCoin(i - 1, x));
    mem[i][x] = res;
    return res;
}
int main()
{
    memset(mem, -1, sizeof(mem));
    int n,x;
    cin>>n>>x;
    for( int i=1;i<=n;i++){
        cin>> D[i];
    }
    cout<< MinCoin(n,x);
}
