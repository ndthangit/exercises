/*
Một hình chữ nhật kích thước n x m được chia thành các ô vuông con 1 x 1 với 2 màu đen hoặc trắng. Hình chữ nhật được biểu diễn bởi ma trận A(n x m) trong đó A(i, j) = 1 có nghĩa ô hàng i, cột j là ô đen và A(i, j) = 0 có nghĩa ô vuông hàng i cột j là ô trắng.
Hãy xác định hình chữ nhật con của bảng đã cho bao gồm toàn ô đen và có diện tích lớn nhất.
Dữ liệu
· Dòng 1: chứa số nguyên dương n và m (1 <= n,m <= 1000)
· Dòng i+1 (i = 1,…, n): chứa hàng thứ i của ma trận A
Kết quả
· Ghi ra diện tích của hình chữ nhật lớn nhất tìm được
Ví dụ
Dữ liệu
4 4
0 1 1 1
1 1 1 0
1 1 0 0
1 1 1 0
Kết quả
6
*/

#include <bits/stdc++.h>
using namespace std;

int maxHist(vector<int> row){
    stack<int> s;
    int max_area = 0;
    int tp;
    int area_with_top;
    int i = 0;
    while(i < row.size()){
        if(s.empty() || row[s.top()] <= row[i]){
            s.push(i++);
        }else{
            tp = s.top();
            s.pop();
            area_with_top = row[tp] * (s.empty() ? i : i - s.top() - 1);
            if(max_area < area_with_top){
                max_area = area_with_top;
            }
        }
    }
    while(s.empty() == false){
        tp = s.top();
        s.pop();
        area_with_top = row[tp] * (s.empty() ? i : i - s.top() - 1);
        if(max_area < area_with_top){
            max_area = area_with_top;
        }
    }
    return max_area;
}

int maximumRectangleArea(vector<vector<int>> table){
    int result = maxHist(table[0]);
    for(int i = 1; i < table.size(); i++){
        for(int j = 0; j < table[i].size(); j++){
            if(table[i][j]){
                table[i][j] += table[i - 1][j];
            }
        }
        result = max(result, maxHist(table[i]));
    }
    return result;
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> table(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> table[i][j];
        }
    }
    cout<< maximumRectangleArea(table);
    return 0;
}