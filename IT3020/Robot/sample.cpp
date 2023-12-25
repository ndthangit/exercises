#include <bits/stdc++.h>
const int MAXN = 1e2 + 1;
const int inf = 1e9 + 7;
std::vector<std::pair<int, int>> adj[MAXN];
int dist[MAXN][MAXN];
std::vector<int> ke[MAXN];
int n, m, a, b, c, d, r;
std::pair<int, int> parent[MAXN][MAXN];

void inp()
{
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        dist[u][v] = dist[v][u] = w;
        ke[u].push_back(v);
        ke[v].push_back(u);
    }
    std::cin >> a >> b >> c >> d >> r;
}

void floyd()
{
    for (int i = 0; i < n; i++)
    {
        dist[i][i] = 0;
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (i != k)
                for (int j = 0; j < n; j++)
                    if (i != k && j != k)
                        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
}

int ok = 0;
bool visited[MAXN][MAXN];
std::queue<std::pair<int, int>> q;
struct edge
{
    int u, v;
    int w;
};
void bfs(int u, int v)
{
    visited[u][v] = true;
    q.push({u, v});

    while (!q.empty())
    {
        std::pair<int, int> p = q.front();
        q.pop();
        int k1 = p.first;
        int k2 = p.second;

        if (k1 == c && k2 == d)
        {
            ok = 1;
            int tmp1 = k1, tmp2 = k2;
            std::vector<std::pair<int, int>> path;
            while (tmp1 != a || tmp2 != b)
            {
                path.push_back({tmp1, tmp2});
                int next1 = parent[tmp1][tmp2].first;
                int next2 = parent[tmp1][tmp2].second;
                tmp1 = next1;
                tmp2 = next2;
            }
            path.push_back({a, b});
            std::reverse(path.begin(), path.end());
            for (auto x : path)
            {
                std::cout << x.first << " " << x.second << " " << dist[x.first][x.second];
                std::cout << std::endl;
            }
            return;
        }

        for (int k3 : ke[k1])
        {
            if (!visited[k3][k2] && dist[k3][k2] > r)
            {
                parent[k3][k2] = {k1, k2};
                visited[k3][k2] = true;
                q.push({k3, k2});
            }
        }

        for (int k4 : ke[k2])
        {
            if (!visited[k1][k4] && dist[k1][k4] > r)
            {
                parent[k1][k4] = {k1, k2};
                visited[k1][k4] = true;
                q.push({k1, k4});
            }
        }
    }
}

int main()
{
    std::memset(dist, inf, sizeof(dist));
    inp();
    floyd();
    bfs(a, b);

    if (!ok)
    {
        std::cout << "Khong ton tai duong di" << std::endl;
    }

    return 0;
}