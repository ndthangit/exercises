/*bai 2.8 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int val1_thangnd, val2_thangnd;
    cin >> val1_thangnd >> val2_thangnd;

    vector<vector<int>> a_thangnd = {
        {1, 3, 7},
        {2, 3, 4, val1_thangnd},
        {9, 8, 15},
        {10, val2_thangnd},
    };

    //# sắp xếp các vector trong a_thangnd theo tổng các phần tử giảm dần
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    sort(a_thangnd.begin(), a_thangnd.end(), [](const vector<int> &x_thangnd, const vector<int> &y_thangnd) {
        return accumulate(x_thangnd.begin(), x_thangnd.end(), 0) > accumulate(y_thangnd.begin(), y_thangnd.end(), 0);
    });
    

    for (const auto &v_thangnd : a_thangnd) {
        for (int it_thangnd : v_thangnd) {
            cout << it_thangnd << ' ';
        }
        cout << endl;
    }

    return 0;
}
/*bai 2.8 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
