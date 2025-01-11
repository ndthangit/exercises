/*bai 3.2 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <iostream>
using namespace std;

int n_thangnd; // # Kích thước bàn cờ
int X_thangnd[100], Y_thangnd[100]; // # Lưu tọa độ các bước di chuyển của quân mã
int mark_thangnd[100][100]; // # Đánh dấu vị trí các ô mà quân mã đã di chuyển qua

// # Mảng hx_thangnd, hy_thangnd mô tả 8 vị trí quân mã có thể di chuyển kể từ vị trí hiện tại
const int hx_thangnd[] = {1, 1, 2, 2, -1, -1, -2, -2};
const int hy_thangnd[] = {2, -2, 1, -1, 2, -2, 1, -1};

// # In ra dãy các di chuyển tìm được
void print_sol_thangnd()
{
    for (int j = 1; j <= n_thangnd * n_thangnd; ++j)
        printf("(%d %d)\n", X_thangnd[j], Y_thangnd[j]);
    exit(0);
}

// # Thuật toán quay lui
void TRY_thangnd(int k)
{
    for (int i = 0; i < 8; i++)
    {
        int xx_thangnd = X_thangnd[k - 1] + hx_thangnd[i];
        int yy_thangnd = Y_thangnd[k - 1] + hy_thangnd[i];
        /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */

        if (k == n_thangnd * n_thangnd + 1)
        {
            print_sol_thangnd();
        }
        else
        {
            if (xx_thangnd <= n_thangnd && xx_thangnd > 0 && yy_thangnd > 0 && yy_thangnd <= n_thangnd && mark_thangnd[xx_thangnd][yy_thangnd] == 0)
            {
                X_thangnd[k] = xx_thangnd;
                Y_thangnd[k] = yy_thangnd;
                mark_thangnd[xx_thangnd][yy_thangnd] = 1;
                TRY_thangnd(k + 1);
                mark_thangnd[xx_thangnd][yy_thangnd] = 0;
            }
        }
    }
}

int main()
{
    cin >> n_thangnd; // # Nhập kích thước bàn cờ
    mark_thangnd[1][1] = 1; // # Đánh dấu ô đầu tiên
    X_thangnd[1] = Y_thangnd[1] = 1; // # Khởi tạo vị trí xuất phát
    TRY_thangnd(2); // # Bắt đầu thuật toán quay lui từ bước thứ 2
    return 0;
}
/*bai 3.2 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
