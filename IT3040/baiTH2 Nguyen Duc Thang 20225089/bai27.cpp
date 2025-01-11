/*bai 2.7 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <iostream>
using namespace std;

// # viết hàm arr_sum_thangnd
/*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
template <class T>
T arr_sum(T a_thangnd[], int n_thangnd, T b_thangnd[], int m_thangnd)
{
    T sum_thangnd = 0;
    for (int i_thangnd = 0; i_thangnd < n_thangnd; i_thangnd++)
        sum_thangnd += a_thangnd[i_thangnd];
    for (int i_thangnd = 0; i_thangnd < m_thangnd; i_thangnd++)
        sum_thangnd += b_thangnd[i_thangnd];
    return sum_thangnd;
}

int main()
{
    int val_thangnd;
    cin >> val_thangnd;

    {
        int a_thangnd[] = {3, 2, 0, val_thangnd};
        int b_thangnd[] = {5, 6, 1, 2, 7};
        cout << arr_sum(a_thangnd, 4, b_thangnd, 5) << endl;
    }
    {
        double a_thangnd[] = {3.0, 2, 0, val_thangnd * 1.0};
        double b_thangnd[] = {5, 6.1, 1, 2.3, 7};
        cout << arr_sum(a_thangnd, 4, b_thangnd, 5) << endl;
    }

    return 0;
}
/*bai 2.7 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
