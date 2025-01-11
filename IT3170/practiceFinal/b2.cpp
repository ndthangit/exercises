#include<bits/stdc++.h>
using namespace std;

struct khoi
{
    int x,y,z;
};

int dp[200][200][200];
int numtest;
vector<khoi> dskhoi;


int solve( int l,int w, int h)
{
    if( dp[l][w][h] != -1) return dp[l][w][h];
    int waste =l*w*h;

    for( int i=1; i<l; i++)
    {
        waste = min(waste, solve(i,w,h)+solve(l-i,w,h));
    }
    for( int i=1; i<w; i++)
    {
        waste = min(waste, solve(l,i,h)+solve(l,w-i,h));
    }
    for( int i=1; i<h; i++)
    {
        waste = min(waste, solve(l,w,i)+solve(l,w,h-i));
    }
    return dp[l][w][h]= waste;
}
int main()
{

    cin>> numtest;
    while(numtest--)
    {
        memset(dp,-1, sizeof(dp));
        dskhoi.clear();
        int a,b,c;
        cin>> a>> b>> c;
        int n;
        cin>> n;
        for( int i=0; i<n; i++)
        {
            khoi taokhoi;
            cin>> taokhoi.x>> taokhoi.y>> taokhoi.z;
            dskhoi.push_back(taokhoi);

        }

        for( khoi &box : dskhoi)
        {
            dp[box.x][box.y][box.z] = 0;
            dp[box.x][box.z][box.y] = 0;
            dp[box.y][box.x][box.z] = 0;
            dp[box.y][box.z][box.x] = 0;
            dp[box.z][box.x][box.y] = 0;
            dp[box.z][box.y][box.x] = 0;

        }
        cout<< solve(a,b,c)<< endl;
    }

}
