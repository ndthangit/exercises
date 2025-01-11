/*bai 3.3 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <bits/stdc++.h>
using namespace std;
#define MAX 100

int n_thangnd, c_thangnd[MAX][MAX]; // # số thành phố và ma trận chi phí
int cmin_thangnd = INT_MAX;         // # chi phí đi lại nhỏ nhất giữa hai thành phố khác nhau
int best_thangnd = INT_MAX;         // # tổng chi phí nhỏ nhất cần tìm, ban đầu đặt bằng giá trị vô cùng lớn INT_MAX = 2^31-1
int curr_thangnd = 0;               // # tổng chi phí tới thời điểm hiện tại
int mark_thangnd[MAX];              // # đánh dấu những thành phố đã đi
int x_thangnd[MAX];                 // # lưu giữ các thành phố đã đi

// # Đọc dữ liệu vào
void input_thangnd()
{
    cin >> n_thangnd; // # Số lượng thành phố
    for (int i = 1; i <= n_thangnd; ++i)
        for (int j = 1; j <= n_thangnd; ++j)
        {
            cin >> c_thangnd[i][j];            // # Ma trận chi phí
            if (c_thangnd[i][j] > 0 && i != j) // # Tìm chi phí nhỏ nhất giữa hai thành phố khác nhau
                cmin_thangnd = min(cmin_thangnd, c_thangnd[i][j]);
        }
}

// # Thuật toán quay lui
void TRY_thangnd(int k_thangnd)
{
    for (int i = 2; i <= n_thangnd; i++) // # Thử các thành phố từ 2 đến n
    {
        if (mark_thangnd[i] == 0) // # Thành phố chưa được đi qua
        {
            x_thangnd[k_thangnd] = i;
            curr_thangnd += c_thangnd[x_thangnd[k_thangnd - 1]][x_thangnd[k_thangnd]];
            mark_thangnd[i] = 1;
            /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */

            if (k_thangnd == n_thangnd) // # Nếu đã đi qua tất cả các thành phố
            {
                curr_thangnd += c_thangnd[x_thangnd[k_thangnd]][x_thangnd[1]];
                best_thangnd = min(best_thangnd, curr_thangnd);
                curr_thangnd -= c_thangnd[x_thangnd[k_thangnd]][x_thangnd[1]];
            }
            /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */

            else if (curr_thangnd + cmin_thangnd * (n_thangnd - k_thangnd + 1) < best_thangnd) // # Nhánh cận
            {
                TRY_thangnd(k_thangnd + 1); // # Thử thành phố tiếp theo
            }

            curr_thangnd -= c_thangnd[x_thangnd[k_thangnd - 1]][x_thangnd[k_thangnd]];
            mark_thangnd[i] = 0; // # Hoàn nguyên trạng thái
        }
    }
}

int main()
{
    input_thangnd();      // # Đọc dữ liệu vào
    x_thangnd[1] = 1;     // # Thành phố xuất phát là 1
    mark_thangnd[1] = 1;  // # Đánh dấu thành phố xuất phát
    TRY_thangnd(2);       // # Bắt đầu quay lui từ thành phố thứ 2
    cout << best_thangnd; // # In ra chi phí nhỏ nhất
    return 0;
}
/*bai 3.3 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
