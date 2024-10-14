/*
Cho dãy a1, a2, ..., an trong đó các phần tử đôi một khác nhau và 1 giá trị nguyên dương M. Hãy đếm số Q các cặp (i,j) sao cho 1 <= i < j <= n và ai + aj = M.

Dữ liệu
Dòng 1: ghi n và M (1 <= n, M <= 1000000)
Dòng 2: ghi a1, a2, ..., an
Kết quả
Ghi ra giá trị Q
Ví dụ
Dữ liệu
5 6
5 2 1 4 3
Kết quả
2
*/
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
int n,m;
vector<int> arr;

int solve(){
    int dem=0;
    unordered_set<int> a;
    for( int i= 0;i<n;i++){

        if(a.find(m-arr[i]) != a.end()){
            dem++;

        }
        a.insert(arr[i]);
    }
    return dem;
}
int main(){
    cin>> n>>m;
    arr.resize(n);
    for( int i=0; i< n;i++){
        cin>> arr[i];
    }
    cout<< solve();
    return 0;
}
