#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5; // Maximum array size
int a[N], b[N];

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        if (n != m) {
            cout << 0 << endl;
            continue;
        }

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < m; i++) {
            cin >> b[i];
        }

        bool isEqual = true;
        for (int i = 0; i < n; i++) {
            if (a[i] != b[i]) {
                isEqual = false;
                break;
            }
        }

        cout << (isEqual ? 1 : 0) << endl;
    }

    return 0;
}
