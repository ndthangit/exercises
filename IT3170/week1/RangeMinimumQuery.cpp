/*Given a sequence of n integers a
0
,. . .,a
n-1
. We denote rmq(i,j) the minimum element of the sequence a
i
, a
i+1
, . . .,a
j
. Given m pairs (i
1
, j
1
),. . .,(i
m
, j
m
), compute the sum Q = rmq(i
1
,j
1
) + . . . + rmq(i
m
, j
m
)
Input
Line 1: n (1 <=  n <= 10
6
)
Line 2: a
0
, . . . ,a
n-1
 ( 1  <=  ai <= 10
6
)
line 3: m (1  <= m <= 10
6
)
Line k+3 (k=1, . . ., m): i
k
, j
k
 (0  <=  i
k
 < j
k
 < n)
Output
Write the value Q
Example
Input
16
2 4 6 1 6 8 7 3 3 5 8 9 1 2 6 4
4
1 5
0 9
1 15
6 10

Output
6*/

#include <bits/stdc++.h>
using namespace std;

int arr[1000000];
int n, m;
int process[30][1000000];

void build() {
    for (int i = 0; i < n; i++)
        process[0][i] = i;

    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            if (arr[process[j - 1][i]] < arr[process[j - 1][i + (1 << (j - 1))]]) {
                process[j][i] = process[j - 1][i];
            } else {
                process[j][i] = process[j - 1][i + (1 << (j - 1))];
            }
        }
    }
}

int rmq(int i, int j) {
    int k = log2(j - i + 1);
    int p2k = (1 << k);

    if (arr[process[k][i]] <= arr[process[k][j - p2k + 1]]) {
        return process[k][i];
    } else {
        return process[k][j - p2k + 1];
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    build();
    cin >> m;
    int sum = 0;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        sum += arr[rmq(a, b)];
    }
    cout << sum;

    return 0;
}
