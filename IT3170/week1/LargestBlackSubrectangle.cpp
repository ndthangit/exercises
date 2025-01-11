/*A Rectangle of size n x mis divided into unit-square 1 x 1 with two colors black and white. The rectangle is represented by a matrix A(nx m) in which A(i, j) = 1 means that the unit-square at row i, column jis black and A(i, j) = 0 means that the unit-square at row icolumn jis white.
Find the sub-rectangle of the given rectangle containing only black unit-squares such that the area is maximal.
Input
•Line 1: contains 2 positive integers nand m(1 <= n, m<= 1000)
•Line i+1 (i= 1,…, n): contains the ith of the matrix A
Output
Write the area of the sub-rectangle found.

Example
Input
4 4
0 1 1 1
1 1 1 0
1 1 0 0
1 1 1 0
Output
6*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 1;

int a[N][N];

long long h[N];
long long l[N], r[N];

int n, m;

vector<long long> vt;
stack<long long> st;

long long compute()
{
    h[0] = h[m + 1] = -1;
    vt.clear();
    for (int i = 1; i <= m + 1; i++)
    {

        while (!vt.empty() && h[i] < h[vt[vt.size() - 1]])
        {
            r[vt[vt.size() - 1]] = i;
            vt.pop_back();
        }

        vt.push_back(i);
    }
    for (int i = m; i >= 0; i--)
    {

        while (!vt.empty() && h[i] < h[vt[vt.size() - 1]])
        {
            l[vt[vt.size() - 1]] = i;
            vt.pop_back();
        }

        vt.push_back(i);
    }

    unsigned long long ans = 0;

    for (int i = 1; i <= m; i++)
    {

        unsigned long long c = (r[i] - l[i] - 1) * h[i];
        ans = ans < c ? c : ans;
    }

    return ans;
}

void solve()
{
    long long ans = 0;

    for (int i = 1; i <= m; i++)
        h[i] = 0;

    for (int i = 1; i <= n; i++)
    {

        for (int j = 1; j <= m; j++)
        {
            if (a[i][j] == 0)
                h[j] = 0;
            else
                h[j] += 1;
        }

        long long t = compute();

        if (t > ans)
            ans = t;
    }

    cout << ans;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
        }
    }
    solve();
    return 0;
}