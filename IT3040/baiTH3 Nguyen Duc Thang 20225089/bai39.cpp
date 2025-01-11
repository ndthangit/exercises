/*bai 3.9 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <bits/stdc++.h>
using namespace std;
#define MAX_thangnd 100

int n_thangnd, k1_thangnd, k2_thangnd; // lịch làm việc trong n ngày, làm liên tục tối thiểu k1 ngày
                                       // tối đa k2 ngày
int x_thangnd[MAX_thangnd];            // ma trận nhị phân tương ứng ngày i đi làm hoặc không
int count1_thangnd = 0;                // đếm số ngày làm liên tiếp sau 1 ngày nghỉ

// Nhập dữ liệu
void inputData()
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    cin >> n_thangnd >> k1_thangnd >> k2_thangnd;
}

// Kiểm tra xem ngày thứ a được phép làm gì
bool check(int a_thangnd, int i_thangnd)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    if (a_thangnd == 1)
        return true; // nếu là ngày đầu tiên thì làm gì cũng được
    else
    {
        // Nếu ngày a được nghỉ
        if (i_thangnd == 0)
        {
            // Ngày trước đó không được nghỉ
            if (x_thangnd[a_thangnd - 1] == 0)
                return false;
            else
            {
                // Số ngày đi làm liên tiếp phải tối thiểu
                if (count1_thangnd < k1_thangnd)
                    return false;
            }
            // Nếu ngày a đi làm
        }
        else
        {
            // nếu ngày trước đó được nghỉ
            if (x_thangnd[a_thangnd - 1] == 0)
            {
                // Từ ngày a đến ngày n phải đủ tối thiểu số buổi
                if (n_thangnd - a_thangnd + 1 < k1_thangnd)
                    return false;
                // Nếu ngày trước đó đi làm
            }
            else
            {
                // Số ngày đi làm liên tiếp không vượt quá tối đa
                if (count1_thangnd >= k2_thangnd)
                    return false;
            }
        }
        return true;
    }
}

// In ra màn hình kết quả
void solution()
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    for (int i_thangnd = 1; i_thangnd <= n_thangnd; i_thangnd++)
    {
        cout << x_thangnd[i_thangnd];
    }
    cout << endl;
}

// Quay lui
void TRY(int a_thangnd)
{
    for (int i_thangnd = 0; i_thangnd <= 1; i_thangnd++)
    {
        if (check(a_thangnd, i_thangnd))
        {
            x_thangnd[a_thangnd] = i_thangnd;
            int preCount1_thangnd = count1_thangnd;
            // Nếu ngày a đi làm
            /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
            if (i_thangnd == 1)
            {
                // và ngày trước đấy đi làm
                if (x_thangnd[a_thangnd - 1] == 1)
                    count1_thangnd++; // tăng bộ đếm số ngày đi làm liên tiếp
                else
                    count1_thangnd = 1;
            }
            else
            {
                count1_thangnd = 0; // bộ đếm = 0
            }

            if (a_thangnd == n_thangnd)
                solution();
            else
                TRY(a_thangnd + 1);

            count1_thangnd = preCount1_thangnd;
        }
    }
}

int main()
{
    inputData();
    TRY(1);
    return 0;
}
/*bai 3.9 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
