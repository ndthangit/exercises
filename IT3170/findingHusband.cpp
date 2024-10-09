/*
Để tìm kiếm chồng là một anh chàng khoa học máy tính, công chúa của một đất nước ra một đề toán như sau:
Cho n số nguyên, hãy chọn một tập con của tập n số nguyên này sao cho tổng của các số nguyên được chọn không vượt qua M
cho trước và hiệu giữa M và tổng của những số nguyên được chọn là nhỏ nhất.
Đầu vào
· Dòng 1: Số nguyên n (1 <= n <= 20)
· Dòng 2: n số nguyên cách nhau bởi dấu cách, giá trị của các số nguyên này nằm từ 1 tới 1000
· Dòng 3: Số nguyên M (1 <= M <= 100000)
Đầu ra
· Một số tự nhiên là hiệu của M và tổng của các số nguyên được chọn nhỏ nhất.
Ví dụ
Input   (stdin)
5
208   750 114 184 538
897
Output   (stdout)
33
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n; // Số phần tử trong dãy
    cin >> n;
    
    vector<int> arr(n); // Mảng lưu các số nguyên
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int M; // Giá trị M
    cin >> M;

    int best_sum = 0; // Lưu tổng tốt nhất

    // Duyệt qua tất cả các tập con bằng cách sử dụng bitmasking
    for (int mask = 0; mask < (1 << n); mask++) {
        int subset_sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) { // Nếu bit thứ i được bật, thêm phần tử arr[i] vào tổng
                subset_sum += arr[i];
            }
        }
        if (subset_sum <= M && subset_sum > best_sum) {
            best_sum = subset_sum;
        }
    }

    // Tính hiệu giữa M và tổng tốt nhất
    cout << M - best_sum << endl;

    return 0;
}
