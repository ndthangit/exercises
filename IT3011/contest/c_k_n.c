#include <stdio.h>

const long long mod = 1e9 + 7;

long long result[10000][10000];

long long C(int k, int n) {
    if (k == 0 || k == n) {
        result[k][n] = 1;
    } else if (k == 1) {
        result[k][n] = n;
    } else if (result[k][n] == -1) {
        result[k][n] = C(k - 1, n - 1) + C(k, n - 1);
        result[k][n] %= mod;
    }
    return result[k][n];
}

int main() {
    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < 10000; j++) {
            result[i][j] = -1;
        }
    }

    int k, n;
    scanf("%d%d", &k, &n);
    printf("%lld", C(k, n));
    return 0;
}
