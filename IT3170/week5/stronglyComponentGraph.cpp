#include<bits/stdc++.h>
using namespace std;
const int N = 1e4+5;
int n,m,cnt=0;
int dem =0;
int low[N], num[N];
vector<int> ds[N];
stack<int> st;

void solve( int point)
{
    low[point] = num[point] = ++cnt;
    st.push(point);

    for( auto v : ds[point])
    {
        if(num[v])
        {
            low[point] = min(low[point], num[v]);
        }
        else
        {
            solve(v);
            low[point]= min(low[point],low[v]);

        }
    }

    if(num[point] == low[point])
    {
        dem++;
        int tmp;
        do
        {
            tmp = st.top();
            st.pop();
            num[tmp] = low[tmp]= INT_MAX;

        }
        while(tmp != point);
    }

}



int main()
{
    cin>> n>>m;
    memset(low,0,sizeof(low));
    memset(num,0,sizeof(num));


    for( int i=0; i<m; i++)
    {
        int a,b;
        cin>>a>>b;
        ds[a].push_back(b);
    }

    for( int i=1;i<=n;i++){
        if( !num[i]) solve(i);
    }

    cout<< dem;

}
