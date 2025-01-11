/*bai 3.8 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <bits/stdc++.h>
using namespace std;

struct state
{
    int i, j, s;
    state(int _i = 0, int _j = 0, int _s = 0) : i(_i), j(_j), s(_s) {}
};

int main()
{
    int n, M; // // n quả cân và vật có cân nặng M
    cin >> n >> M;
    int m[n + 1]; // ma trận trọng lượng của từng quả cân
    for (int i = 1; i <= n; ++i)
        cin >> m[i];
    int x[n + 1]; // ma trận cài đặt quả cân thứ i được đặt lên cân bên nào hoặc không cân
    stack<state> s;
    s.push(state(1, -1, -m[1])); // Trường hợp quả cân 1 bên vật nặng
    s.push(state(1, 0, 0));      // trường hợp quả cân 1 không được cân
    s.push(state(1, 1, m[1]));   // trường hợp quả cân 1 bên còn lại
    while (!s.empty())
    {
        state top = s.top();
        // Khi đã nạp hết các quả cân vào stack
        if (top.i >= n)
        {
            if (top.s == M)
            { // Nếu khối lượng bằng M thì kiểm tra xem quả cân nào
              // để bên nào hoặc không cân
                for (int i = 1; i <= n; ++i)
                {
                    if (x[i] == -1)
                        cout << '-' << m[i];
                    if (x[i] == 1)
                        cout << '+' << m[i];
                }
                cout << "=" << M;
                exit(0);
            }
            s.pop();
            continue;
        }

        // # Khử đệ quy
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
        s.pop();
        x[top.i] = top.j;
        s.push(state(top.i + 1, -1, top.s - m[top.i + 1])); // Trường hợp quả cân i bên vật nặng
        s.push(state(top.i + 1, 0, top.s));                 // Trường hợp quả cân i không được cân
        s.push(state(top.i + 1, 1, top.s + m[top.i + 1]));  // Trường hợp quả cân i bên còn lại
    }
    cout << -1;

    return 0;
}
/*bai 3.8 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/