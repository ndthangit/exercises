#include <iostream>
#include <vector>
using namespace std;

int findMaxFeasibleSubsequence(int n, int Q, vector<int> arr) {
    int maxLen = 0;
    int currentSum = 0;
    int start = 0;

    for (int end = 0; end < n; end++) {
        currentSum += arr[end];

        while (currentSum > Q) {
            currentSum -= arr[start];
            start++;
        }

        maxLen = max(maxLen, end - start + 1);
    }

    if (maxLen == 0) {
        return -1;
    } else {
        return maxLen;
    }
}

int main() {
    int n, Q;
    cin >> n >> Q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int result = findMaxFeasibleSubsequence(n, Q, arr);
    cout << result << endl;
    return 0;
}
