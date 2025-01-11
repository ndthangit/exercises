#include <bits/stdc++.h>
using namespace std;

int c[15][15], s[7][15], best_s[7][15], vi[15] = {};
int n, k, kni, ki, mn = 1e6, p = 0, cmin = 1e6;

int cal() {
    int dis = 0;
    for (int i = 1; i <= k; ++i) {
        int j = -1, ci = c[0][s[i][0]];
        while (s[i][++j]) {
            ci += c[s[i][j]][s[i][j + 1]];
        }
        dis += ci;
    }
    return dis;
}

void X() {
    if (p == n) {
        int dis = 0;
        for (int i = 1; i <= k; ++i) {
            int j = -1, ci = c[0][s[i][0]];
            while (s[i][++j]) {
                ci += c[s[i][j]][s[i][j + 1]];
            }
            dis += ci;
        }
        if (dis < mn) {
            mn = dis;
            // Store the current best route
            for (int i = 1; i <= k; ++i) {
                int j = 0;
                while (s[i][j]) {
                    best_s[i][j] = s[i][j];
                    j++;
                }
                best_s[i][j] = 0; // Mark the end of the route
            }
        }
        return;
    }

    if (ki < k) {
        int tmp = kni;
        ++ki;
        kni = 1;
        X();
        --ki;
        kni = tmp;
    }

    for (int i = 1; i <= n; ++i) {
        if (!vi[i]) {
            s[ki][kni++] = i;
            ++p;
            vi[i] = 1;
            if (cal() < mn)
                X();
            vi[i] = 0;
            --p;
            s[ki][--kni] = 0;
        }
    }
}

void Y(int a) {
    if (a > k) {
        p = k;
        ki = 1;
        kni = 1;
        X();
        return;
    }
    for (int i = s[a - 1][0] + 1; i <= n; i++) {
        s[a][0] = i;
        vi[i] = 1;
        Y(a + 1);
        vi[i] = 0;
    }
}

int main() {
    cin >> n >> k;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cin >> c[i][j];
            if (c[i][j])
                cmin = min(cmin, c[i][j]);
        }
    }
    int num =k;
    ++k;
    while (--k) {
        Y(1);
    }
    cout << "Minimal Total Distance: " << mn << endl;
    cout << "Routes for each vehicle:" << endl;
    for (int i = 1; i <= num; ++i) {
        cout << "Vehicle " << i << ": 0"; // Start at depot
        int j = 0;
        while (best_s[i][j]) {
            cout << " -> " << best_s[i][j];
            j++;
        }
        cout << " -> 0" << endl; // Return to depot
    }
    return 0;
}
