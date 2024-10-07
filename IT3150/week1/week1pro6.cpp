/*
Given a sequence of integers a1, a2, . . ., an. A k-subsequence is define to be a sequence of k consecutive elements: ai, ai+1, . . ., ai+k-1. The weight of a k-subsequence is the sum of its elements.
Given positive integers k and m. Compute the number Q of k-subsequences such that the weight is even.
Input
Line 1: contains 2 positive integers n, k (1 <= n <= 100000, 1 <= k <= n/2)
Line 2: contains a1, a2, . . ., an. (1 <= ai <= 10000)
Output
Write the value Q
Example
Input
6  3
2 4 5 1 1 2
Output
2
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    long n, k;
    cin >> n >> k;
    vector<long> arr(n);
    for (long i = 0; i < n; i++)
    {
        cin>> arr[i];
    }
    long count = 0;
    long sum = 0;
    for (long  i = 0; i < k; i++)
    {
        sum+= arr[i];
    }
    if (sum % 2 == 0)
    {
        count++;
    }
    for (long i = k; i < n; i++)
    {
        sum+= arr[i];
        sum-= arr[i-k];
        if (sum % 2 == 0)
        {
            count++;
        }
    }
    
    cout<< count;

    
}