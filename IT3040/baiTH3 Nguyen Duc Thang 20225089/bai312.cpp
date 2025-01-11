/*bai 3.12 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <bits/stdc++.h>
using namespace std;
#define MAX_thangnd 100
int n_thangnd, k_thangnd;          // Số đỉnh là n, số cạnh đi qua là k
int m_thangnd;                     // số cạnh của đồ thị là m
vector<vector<int>> vt_thangnd;    // Chuyển từ lưu trữ các cạnh sang lưu trữ danh sách kề
int x_thangnd[MAX_thangnd];        // lưu trữ thứ tự đi qua các đỉnh
bool visited_thangnd[MAX_thangnd]; // lưu trữ đỉnh nào được đi qua
int res_thangnd;                   // số lượng đường đi độ dài k

void input()
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    cin >> n_thangnd >> k_thangnd;
    cin >> m_thangnd;
    vt_thangnd.resize(n_thangnd + 1);
    for (int i_thangnd = 0; i_thangnd < m_thangnd; i_thangnd++)
    {
        /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
        int tmp1_thangnd, tmp2_thangnd;
        cin >> tmp1_thangnd >> tmp2_thangnd; // nhập các cạnh của đồ thị

        vt_thangnd[tmp1_thangnd - 1].push_back(tmp2_thangnd - 1); // đỉnh tmp2_thangnd kề với đỉnh tmp1_thangnd
        vt_thangnd[tmp2_thangnd - 1].push_back(tmp1_thangnd - 1); // đỉnh tmp1_thangnd kề với đỉnh tmp2_thangnd
    }

    for (int i_thangnd = 0; i_thangnd < n_thangnd; i_thangnd++)
    {
        visited_thangnd[i_thangnd] = false; // mặc định các đỉnh chưa được thăm
    }
    res_thangnd = 0;
}

bool check(int a_thangnd, int i_thangnd)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    if (a_thangnd == 0)
        return true; // Lần đầu luôn đúng
    if (visited_thangnd[i_thangnd])
        return false; // nếu i_thangnd đã thăm thì thôi

    // Kiểm tra xem đỉnh trước đấy có kề với đỉnh i_thangnd không
    for (int j_thangnd = 0; j_thangnd < vt_thangnd[x_thangnd[a_thangnd - 1]].size(); j_thangnd++)
    {
        if (i_thangnd == vt_thangnd[x_thangnd[a_thangnd - 1]][j_thangnd])
            return true;
    }

    return false;
}

// Tăng số lượng đường đi lên 1
void solution()
{
    res_thangnd++;
}

// Quay lui
void TRY(int a_thangnd)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    for (int i_thangnd = 0; i_thangnd < n_thangnd; i_thangnd++)
    {
        // Kiểm tra lần thứ a_thangnd đi qua i_thangnd có hợp lệ không
        if (check(a_thangnd, i_thangnd))
        {
            visited_thangnd[i_thangnd] = true;
            x_thangnd[a_thangnd] = i_thangnd;

            if (a_thangnd == k_thangnd)
                solution();
            else
                TRY(a_thangnd + 1);

            visited_thangnd[i_thangnd] = false;
        }
    }
}

int main()
{
    input();
    TRY(0);
    cout << res_thangnd / 2; // số lượng đường đi đơn độ dài k
    return 0;
}
/*bai 3.12 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/