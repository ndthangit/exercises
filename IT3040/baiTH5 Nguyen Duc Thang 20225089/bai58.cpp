/*bai 5.8 - tuần 17
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <bits/stdc++.h>

using namespace std;

int w, h;
int table[601][601];

void init()
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            table[i][j] = i * j;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie();

    int m;
    cin >> w >> h;
    cin >> m;
    init();
    for (int i = 0; i < m; i++)
    {
        /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;
        table[tmp2][tmp1] = 0;
    }

    // dp
    for (int i = 1; i <= h; i++)
    {
        /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
        for (int j = 1; j <= w; j++)
        {
            int minWaste = table[i][j];
            // horizonal cut
            for (int k = 1; k <= i; k++)
            {
                minWaste = min(minWaste, table[k][j] + table[i - k][j]);
            }
            // vertical cut
            for (int k = 1; k <= j; k++)
            {
                minWaste = min(minWaste, table[i][k] + table[i][j - k]);
            }
            table[i][j] = minWaste;
        }
    }

    cout << table[h][w] << endl;
}
/*bai 5.8 - tuần 17
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/