/*bai 3.4 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <bits/stdc++.h>
using namespace std;
int a[1000], n;
int mem[1000]; //# mảng ghi nhớ lời giải các bài toán con đã được giải

void init(){
    memset(mem, -1, sizeof(mem));
}

//# Quy hoạch động, 
//# Hàm lis(i) trả về độ dài dãy con tăng dài nhất kết thúc bởi a[i]
int lis(int i) {
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
   if (mem[i] != -1) {
        return mem[i];
    }
    
    int res = 1; 
    for(int j = 0; j < i; j++){
        if (a[j] < a[i]){
            res = max(res, lis(j) + 1);
        }
    }
    
    mem[i] = res; 
    return res;

}

//# Truy vet loi giai
void trace(int i){
    for(int j = 0; j < i; j++){
        if (a[j] < a[i] && mem[i] == 1 + mem[j]){
            trace(j);
            break;
        }
    }
    cout << a[i] << " ";
}

int main(){
    init();
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    int res = 1, pos = 0;
    for(int i = 1; i < n; i++){
        if (res < lis(i)){
            res = lis(i);
            pos = i;
        }
    }
    cout << res << endl;
    trace(pos);
    return 0;
}
/*bai 3.4 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/