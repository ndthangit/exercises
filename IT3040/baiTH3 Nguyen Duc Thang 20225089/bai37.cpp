/*bai 3.7 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <bits/stdc++.h>
using namespace std;

struct state
{
    int i, j, old_L;
    state(int _i = 0, int _j = 0, int _L = 0) : i(_i), j(_j), old_L(_L) {}
};

int main()
{
    int n, k;
    cin >> n >> k;
    int x[n + 1];
    stack<state> s;
    int L = 0;
    s.push(state(1, 0));
    while (!s.empty())
    {
        state &top = s.top();
        if (top.i > n)
        {
            for (int i = 1; i <= n; ++i)
                cout << x[i] << " \n"[i == n];
            s.pop();
            continue;
        }

        // # Khử đệ quy
        /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
        int i_thangnd = top.i, j_thangnd = top.j, old_L_thangnd = top.old_L;
        s.pop();

        x[i_thangnd] = j_thangnd;

        if (j_thangnd)
        {
            L = old_L_thangnd + 1;
        }
        else
        {
            L = 0;
            if (old_L_thangnd + 1 < k)
            {

                s.push(state(i_thangnd, 1, old_L_thangnd));
            }
        }
        s.push(state(i_thangnd + 1, 0, L));
    }
    return 0;
}
/*bai 3.7 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/