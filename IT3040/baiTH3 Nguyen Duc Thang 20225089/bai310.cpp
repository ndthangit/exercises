/*bai 3.10 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <bits/stdc++.h>
using namespace std;
#define MAX_thangnd 16

int N_thangnd, H_thangnd;
int x_thangnd[MAX_thangnd];
int S_thangnd[MAX_thangnd];

void input()
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    cin >> N_thangnd >> H_thangnd;
    for (int i_thangnd = 0; i_thangnd < N_thangnd; i_thangnd++)
    {
        S_thangnd[i_thangnd] = 0;
        x_thangnd[i_thangnd] = 0;
    }
}

int hammingDistance(int x_thangnd[], int S_thangnd[])
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    int count_thangnd = 0;
    for (int i_thangnd = 0; i_thangnd < N_thangnd; i_thangnd++)
    {
        if (x_thangnd[i_thangnd] != S_thangnd[i_thangnd])
            count_thangnd++;
    }
    return count_thangnd;
}

void solution()
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    for (int i_thangnd = 0; i_thangnd < N_thangnd; i_thangnd++)
    {
        cout << x_thangnd[i_thangnd];
    }
    cout << endl;
}

// Quay lui
void TRY(int k_thangnd)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    for (int i_thangnd = 0; i_thangnd <= 1; i_thangnd++)
    {
        x_thangnd[k_thangnd] = i_thangnd;
        if (k_thangnd == N_thangnd - 1)
        {

            if (hammingDistance(x_thangnd, S_thangnd) == H_thangnd)
            {
                solution();
            }
        }
        else
        {
            TRY(k_thangnd + 1);
        }
    }
}

int main()
{
    int T_thangnd; // Số testcase
    cin >> T_thangnd;
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    while (T_thangnd > 0)
    {
        input();
        TRY(0);
        cout << endl;
        T_thangnd--;
    }
    return 0;
}
/*bai 3.10 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
