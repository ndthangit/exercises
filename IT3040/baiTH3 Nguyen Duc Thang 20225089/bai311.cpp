/*bai 3.11 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <bits/stdc++.h>
using namespace std;
#define MAX_thangnd 10000

int n_thangnd, r_thangnd;                    // kích thước ma trận nxn, số người đưa ra yêu cầu là r
int price_thangnd[MAX_thangnd][MAX_thangnd]; // ma trận chi phí
int x_thangnd[MAX_thangnd];
bool visited_thangnd[MAX_thangnd];
vector<int> vt_thangnd;
int min_price_thangnd;
int sum_price_thangnd;
int start_thangnd, destination_thangnd, numberOfPoint_thangnd;
queue<int> res;

void input()
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    cin >> n_thangnd >> r_thangnd;
    for (int i_thangnd = 0; i_thangnd < n_thangnd; i_thangnd++)
        for (int j_thangnd = 0; j_thangnd < n_thangnd; j_thangnd++)
        {
            cin >> price_thangnd[i_thangnd][j_thangnd];
        }
}

bool check(int a_thangnd, int i_thangnd)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    if (visited_thangnd[vt_thangnd[i_thangnd]])
        return false;
    if (price_thangnd[x_thangnd[a_thangnd - 1]][vt_thangnd[i_thangnd]] == 0)
        return false;
    return true;
}

void solution()
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    if (price_thangnd[x_thangnd[numberOfPoint_thangnd - 2]][destination_thangnd] == 0)
        return;
    min_price_thangnd = min(min_price_thangnd, sum_price_thangnd + price_thangnd[x_thangnd[numberOfPoint_thangnd - 2]][destination_thangnd]);
}

void TRY(int a_thangnd)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    for (int i_thangnd = 1; i_thangnd < numberOfPoint_thangnd - 1; i_thangnd++)
    {
        if (check(a_thangnd, i_thangnd))
        {
            /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
            visited_thangnd[vt_thangnd[i_thangnd]] = true;
            sum_price_thangnd += price_thangnd[x_thangnd[a_thangnd - 1]][vt_thangnd[i_thangnd]];

            x_thangnd[a_thangnd] = vt_thangnd[i_thangnd];
            if (a_thangnd == numberOfPoint_thangnd - 2)
                solution();
            else
                TRY(a_thangnd + 1);
            /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
            visited_thangnd[vt_thangnd[i_thangnd]] = false;
            sum_price_thangnd -= price_thangnd[x_thangnd[a_thangnd - 1]][vt_thangnd[i_thangnd]];
        }
    }
}

int main()
{
    string str_thangnd;
    input();
    getline(cin, str_thangnd);

    while (r_thangnd > 0)
    {
        /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
        min_price_thangnd = INT_MAX;
        sum_price_thangnd = 0;

        getline(cin, str_thangnd);

        while (!str_thangnd.empty())
        {
            stringstream convert_thangnd(str_thangnd.substr(0, str_thangnd.find(" ")));
            int tmp_thangnd = 0;
            convert_thangnd >> tmp_thangnd;
            vt_thangnd.push_back(tmp_thangnd - 1);

            if (str_thangnd.find(" ") > str_thangnd.size())
            {
                break;
            }
            else
            {
                str_thangnd.erase(0, str_thangnd.find(" ") + 1); // Cập nhật chuỗi
            }
        }

        // Khởi tạo các dữ liệu
        start_thangnd = vt_thangnd[0];                           // điểm bắt đầu
        destination_thangnd = vt_thangnd[vt_thangnd.size() - 1]; // điểm đích
        numberOfPoint_thangnd = vt_thangnd.size();               // số điểm phải đi qua
        x_thangnd[0] = start_thangnd;
        x_thangnd[numberOfPoint_thangnd - 1] = destination_thangnd;
        for (int i_thangnd = 0; i_thangnd < n_thangnd; i_thangnd++)
            visited_thangnd[i_thangnd] = false;
        /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
        TRY(1);

        // in kết quả
        if (min_price_thangnd == INT_MAX)
            cout << "0" << endl;
        else
            cout << min_price_thangnd << endl;

        // Xóa vector và chuyển sang yêu cầu người tiếp theo
        vt_thangnd.erase(vt_thangnd.begin(), vt_thangnd.end());
        r_thangnd--;
    }
    
    return 0;
}
/*bai 3.11 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
