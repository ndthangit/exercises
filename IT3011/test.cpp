#include <bits/stdc++.h>

using namespace std;
const long long N = 1e5 + 5, inf = 1e15;
vector<pair<long long, long long>> ed[N];
int main()
{
    long long n, m, s, t, dis[N];
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (long long i = 1; i <= m; i++)
    {
        long long u, v, w;
        cin >> u >> v >> w;
        ed[u].push_back(make_pair(v, w));
    }
    cin >> s >> t;

    set<pair<long long, long long>> st;
    st.insert(make_pair(0, s));

    for (long long i = 1; i <= n; i++)
        dis[i] = inf;
    dis[s] = 0;

    while (!st.empty())
    {
        long long u = st.begin()->second;
        st.erase(st.begin());

        for (pair<long long, long long> tmp : ed[u])
        {
            long long v = tmp.first, w = tmp.second;

            if (dis[v] > dis[u] + w)
            {
                st.erase(make_pair(dis[v], v));
                dis[v] = dis[u] + w;
                st.insert(make_pair(dis[v], v));
            }
        }
    }

    if (dis[t] == inf)
        cout << "-1\n";
    else
        cout << dis[t] << '\n';
}