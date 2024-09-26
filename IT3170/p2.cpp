#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // vector<vector<int>> table(n, vector<int>(m));
    // vector<vector<int>> prefix_sum(n + 1, vector<int>(m + 1, 0));

    int table[n][m];
    int prefix_sum[n + 1][m + 1];

    // Read input table
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> table[i][j];
        }
    }

    // Build prefix sum array
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            prefix_sum[i][j] = table[i - 1][j - 1] + prefix_sum[i - 1][j] + prefix_sum[i][j - 1] - prefix_sum[i - 1][j - 1];
        }
    }

    // Process queries
    int q;
    cin >> q;
    for (int k = 0; k < q; ++k) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        int result = prefix_sum[r2][c2] - prefix_sum[r2][c1 - 1] - prefix_sum[r1 - 1][c2] + prefix_sum[r1 - 1][c1 - 1];
        cout << result << "\n";
    }

    return 0;
}
