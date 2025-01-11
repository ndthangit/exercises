/*bai 4.12 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include<bits/stdc++.h>
using namespace std;

// Khai báo các biến toàn cục
long long n_thangnd; // Số lượng phần tử trong mảng
vector<long long> vt_thangnd; // Mảng chứa các giá trị đầu vào
vector<long long> L_thangnd; // Mảng trái, lưu vị trí phần tử bên trái gần nhất nhỏ hơn phần tử đang xét
vector<long long> R_thangnd; // Mảng phải, lưu vị trí phần tử bên phải gần nhất nhỏ hơn phần tử đang xét

// Hàm nhập dữ liệu từ file input1.txt
// Nhập số phần tử và các giá trị của mảng, thêm lính canh (-1) ở hai đầu mảng
void inputData() {
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    ifstream infile("input1.txt"); // Mở file input1.txt
    infile >> n_thangnd; // Đọc số phần tử
    vt_thangnd.push_back(-1); // Đặt lính canh ở đầu mảng
    for(long long i_thangnd = 0; i_thangnd < n_thangnd; i_thangnd++) {
        long long tmp_thangnd;
        infile >> tmp_thangnd; // Đọc giá trị từ file
        vt_thangnd.push_back(tmp_thangnd); // Đẩy giá trị vào mảng
    }
    vt_thangnd.push_back(-1); // Đặt lính canh ở cuối mảng
    infile.close(); // Đóng file sau khi đọc xong
}

// Hàm xử lý chính
// Tính toán giá trị lớn nhất của hình chữ nhật có thể tạo thành trong biểu đồ histogram
void solve() {
    while(true) {
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
        inputData(); // Gọi hàm nhập dữ liệu từ file
        if(n_thangnd == 0) return; // Nếu không có phần tử nào, thoát chương trình

        // Khởi tạo stack để tính toán mảng L và R
        stack<long long> st_thangnd; 
        L_thangnd.resize(n_thangnd + 2); // Mảng L có kích thước n+2, bao gồm lính canh
        R_thangnd.resize(n_thangnd + 2); // Mảng R tương tự

        // Xây dựng mảng L (trái)
        for(long long i_thangnd = 1; i_thangnd <= n_thangnd + 1; i_thangnd++) {
            while(!st_thangnd.empty() && vt_thangnd[i_thangnd] < vt_thangnd[st_thangnd.top()]) { 
                L_thangnd[st_thangnd.top()] = i_thangnd; // Lưu vị trí phần tử nhỏ hơn bên trái gần nhất
                st_thangnd.pop();        // Xóa phần tử trên đỉnh stack
            }
            st_thangnd.push(i_thangnd); // Đẩy phần tử hiện tại vào stack
        }
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

        // Xây dựng mảng R (phải)
        for(long long i_thangnd = n_thangnd; i_thangnd >= 0; i_thangnd--) {
            while(!st_thangnd.empty() && vt_thangnd[i_thangnd] < vt_thangnd[st_thangnd.top()]) { 
                R_thangnd[st_thangnd.top()] = i_thangnd; // Lưu vị trí phần tử nhỏ hơn bên phải gần nhất
                st_thangnd.pop();        // Xóa phần tử trên đỉnh stack
            }
            st_thangnd.push(i_thangnd); // Đẩy phần tử hiện tại vào stack
        }

        // Tính diện tích hình chữ nhật lớn nhất
        long long maxh_thangnd = 0; // Lưu giá trị lớn nhất
        for(long long i_thangnd = 1; i_thangnd <= n_thangnd; i_thangnd++) {
            long long h_thangnd = (L_thangnd[i_thangnd] - R_thangnd[i_thangnd] - 1) * vt_thangnd[i_thangnd]; // Tính diện tích với chiều cao vt[i]
            if(h_thangnd > maxh_thangnd) maxh_thangnd = h_thangnd; // Cập nhật giá trị lớn nhất
        }

        // In kết quả
        cout << maxh_thangnd << endl; 
        break;

        // Xóa dữ liệu trước khi bắt đầu vòng lặp mới
        vt_thangnd.erase(vt_thangnd.begin(), vt_thangnd.end());
        L_thangnd.erase(L_thangnd.begin(), L_thangnd.end());
        R_thangnd.erase(R_thangnd.begin(), R_thangnd.end());
    }
}

// Hàm main
// Điều khiển luồng thực thi chương trình
int main() {
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    solve(); // Gọi hàm xử lý chính
    return 0;
}

/*bai 4.12 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
