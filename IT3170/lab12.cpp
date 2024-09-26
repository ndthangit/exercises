/*
Một mê cung hình chữ nhật được biểu diễn bởi 0-1 ma trận NxM trong đó A[i,j] = 1 thể hiện ô (i,j) là tường gạch và A[i,j] = 0 thể hiện ô (i,j) là ô trống, có thể di chuyển vào. Từ 1 ô trống, ta có thể di chuyển sang 1 trong 4 ô lân cận (lên trên, xuống dưới, sang trái, sang phải) nếu ô đó là ô trống. Xuất phát từ 1 ô trống trong mê cung, hãy tìm đường ngắn nhất thoát ra khỏi mê cung.

Input
Dòng 1: ghi 4 số nguyên dương n, m, r, c trong đó n và m tương ứng là số hàng và cột của ma trận A (1 <= n,m <= 999) và r, c tương ứng là chỉ số hàng, cột của ô xuất phát.
Dòng i+1 (i=1,...,n): ghi dòng thứ i của ma trận A

Output
Ghi giá số bước cần di chuyển ngắn nhất để thoát ra khỏi mê cung, hoặc ghi giá trị -1 nếu không tìm thấy đường đi nào thoát ra khỏi mê cung.

Ví dụ

Input
8 12 5 6
1 1 0 0 0 0 1 0 0 0 0 1
1 0 0 0 1 1 0 1 0 0 1 1
0 0 1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 1 0 0 1 0 1
1 0 0 1 0 0 0 0 0 1 0 0
1 0 1 0 1 0 0 0 1 0 1 0
0 0 0 0 1 0 1 0 0 0 0 0
1 0 1 1 0 1 1 1 0 1 0 1

Output
7
*/

#include <bits/stdc++.h>
#include <queue>
using namespace std;
typedef pair<int, int> ii;

int solve(vector<vector<int>> maze, int n, int m, int r, int c)
{

    queue<pair<int, int>> q;

    q.push({r, c});
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int count = 0;
    while (!q.empty())
    {
        int size = q.size();
        while (size--)
        {
            ii p = q.front();
            q.pop();
            int x = p.first;
            int y = p.second;
            if (maze[x][y] == 1)
            {
                continue;
            }
            if (x == 0 || y == 0 || x == n - 1 || y == m - 1)
            {
                return count + 1;
            }
            maze[x][y] = 1;
            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (maze[nx][ny] == 0)
                {
                    q.push({nx, ny});
                }
            }
        }
        count++;
    }

    return -1;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, r, c;
    cin >> n >> m >> r >> c;

    vector<vector<int>> maze(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> maze[i][j];
        }
    }
    cout << solve(maze, n, m, r-1, c-1);
    return 0;
}
