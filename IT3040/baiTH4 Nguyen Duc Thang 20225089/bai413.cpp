/*bai 4.13 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include<bits/stdc++.h>
using namespace std;
int n_thangnd;
string str_thangnd;
int cnt_thangnd;
int res_thangnd;
map<int, int> m_thangnd;

void input(){
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    ifstream infile("input2.txt");
    if (!infile) {
        cerr << "Error: Unable to open input2.txt" << endl;
        exit(1); // Thoát chương trình nếu không mở được file
    }
    infile >> str_thangnd;
    infile.close(); // Đóng file sau khi đọc
    n_thangnd = str_thangnd.length();
    cnt_thangnd = 0;
    res_thangnd = 0;
}

int calc(int b_thangnd){
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    int foo_thangnd = 0;
    for(int i_thangnd = 1; i_thangnd < b_thangnd; i_thangnd++)
        foo_thangnd += i_thangnd;
    return foo_thangnd;
}

void solve(){
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    int slg0_thangnd = 0, slg1_thangnd = 0;
    map<int, int>::iterator it_thangnd;

    for(int i_thangnd = 0; i_thangnd < n_thangnd; i_thangnd++){
        if(str_thangnd[i_thangnd] == '0') slg0_thangnd++;
        else slg1_thangnd++;
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

        int tmp_thangnd = slg1_thangnd - slg0_thangnd; // độ chênh lệch 0,1
        it_thangnd = m_thangnd.find(tmp_thangnd);
        if(it_thangnd != m_thangnd.end()){ // nếu độ chênh lệch đã tồn tại
            it_thangnd->second += 1;
        } else {
            m_thangnd.insert({tmp_thangnd, 1});
        }
    }

    it_thangnd = m_thangnd.begin();
    while(it_thangnd != m_thangnd.end()){
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
        res_thangnd += calc(it_thangnd->second);
        if(it_thangnd->first == 0) res_thangnd += it_thangnd->second;
        it_thangnd++;
    }
}

int main(){
    input();
    solve();
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    cout << res_thangnd;
    return 0;
}
/*bai 4.13 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
