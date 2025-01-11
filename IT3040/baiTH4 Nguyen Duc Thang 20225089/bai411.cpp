/*bai 4.11 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <bits/stdc++.h>
using namespace std;

// Số tên giặc và khả năng chống trả của một lính ở một đoạn tường
struct data
{
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    int ai_thangnd; // Số tên giặc ở một đoạn tường
    int ki_thangnd; // Khả năng chống trả tối đa của một lính ở đoạn tường

    // Constructor để khởi tạo giá trị cho struct
    data(int ai_thangnd, int ki_thangnd)
    {
        this->ai_thangnd = ai_thangnd;
        this->ki_thangnd = ki_thangnd;
    }
};

// So sánh các đoạn tường dựa trên số tên giặc có thể tiêu diệt hiệu quả nhất
struct compare
{
    bool operator()(data a_thangnd, data b_thangnd)
    {
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
        int ra_thangnd, rb_thangnd;

        // Tính số tên giặc tiêu diệt hiệu quả nhất cho đoạn a
        if (a_thangnd.ai_thangnd <= a_thangnd.ki_thangnd)
            ra_thangnd = a_thangnd.ai_thangnd;
        else
            ra_thangnd = a_thangnd.ki_thangnd;

        // Tính số tên giặc tiêu diệt hiệu quả nhất cho đoạn b
        if (b_thangnd.ai_thangnd <= b_thangnd.ki_thangnd)
            rb_thangnd = b_thangnd.ai_thangnd;
        else
            rb_thangnd = b_thangnd.ki_thangnd;

        // So sánh dựa trên số giặc tiêu diệt hiệu quả
        return ra_thangnd < rb_thangnd;
    }
};

// Khai báo các biến toàn cục
int n_thangnd, s_thangnd, kill_enemy_thangnd, total_enemy_thangnd;
priority_queue<data, vector<data>, compare> p_q_thangnd;

// Hàm nhập dữ liệu
// Nhập số lượng đoạn tường (n_thangnd) và số lượt lính được sử dụng (s_thangnd)
// Đọc thông tin từng đoạn tường và thêm vào priority queue
void input()
{
    cin >> n_thangnd >> s_thangnd;
    kill_enemy_thangnd = 0;  // Số giặc đã tiêu diệt ban đầu
    total_enemy_thangnd = 0; // Tổng số giặc trên tất cả các đoạn tường
    for (int i_thangnd = 0; i_thangnd < n_thangnd; i_thangnd++)
    {
        int tmp1_thangnd, tmp2_thangnd;
        cin >> tmp1_thangnd >> tmp2_thangnd;
        total_enemy_thangnd += tmp1_thangnd;
        p_q_thangnd.push(data(tmp1_thangnd, tmp2_thangnd));
    }
}

// Hàm xử lý logic
// Sử dụng số lượt lính (s_thangnd) để tiêu diệt số lượng giặc tối đa
void solve()
{
    while (!p_q_thangnd.empty() && s_thangnd > 0)
    {
        // Lấy đoạn tường có hiệu quả tiêu diệt giặc tốt nhất
        data inf_thangnd = p_q_thangnd.top();
        p_q_thangnd.pop();

        // Nếu lính có thể tiêu diệt toàn bộ số giặc ở đoạn tường
        if (inf_thangnd.ai_thangnd <= inf_thangnd.ki_thangnd)
        {
            kill_enemy_thangnd += inf_thangnd.ai_thangnd; // Tiêu diệt toàn bộ
        }
        else
        {
            // Nếu không tiêu diệt hết, tiếp tục xử lý số giặc còn lại
            int nenemy_thangnd = inf_thangnd.ai_thangnd - inf_thangnd.ki_thangnd;
            p_q_thangnd.push(data(nenemy_thangnd, inf_thangnd.ki_thangnd));
            kill_enemy_thangnd += inf_thangnd.ki_thangnd; // Tiêu diệt số tối đa
        }

        s_thangnd -= 1; // Giảm số lượt lính
    }
}

// Hàm tính toán số giặc còn lại
// Trả về tổng số giặc ban đầu trừ đi số giặc đã tiêu diệt
int calc_enemy()
{
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    return total_enemy_thangnd - kill_enemy_thangnd;
}

// Hàm chính
// Điều khiển luồng thực thi chương trình: nhập dữ liệu, xử lý và in kết quả
int main()
{
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    input();              // Nhập dữ liệu
    solve();              // Xử lý logic
    cout << calc_enemy(); // In số giặc còn lại
    return 0;
}
/*bai 4.11 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/