#include <bits/stdc++.h>
using namespace std;

void solve(int a, int b, int c){
    // Đặt cố định số chữ số thập phân là 2
    cout << fixed << setprecision(2);

    if (a == 0) {
        if (b == 0) {
            cout << "NO SOLUTION";
            return;
        } else {
            float d = (float) c;
            cout << (float) d / b;
        }
    } else {
        float delta = b * b - 4 * a * c;
        if (delta < 0) {
            cout << "NO SOLUTION";
        } else if (delta == 0) {
            cout << (float) -b / (2 * a);
        } else {
            float sqrt_delta = sqrt(delta);
            cout << (float)(-b - sqrt_delta) / (2 * a) << " " << (float)(-b + sqrt_delta) / (2 * a);
        }
    }
}

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    solve(a, b, c);
    return 0;
}
