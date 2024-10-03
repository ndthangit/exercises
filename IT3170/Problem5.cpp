#include <bits/stdc++.h>
using namespace std;

long minVal(long x, long y) { return (x < y) ? x : y; }
long getMid(long s, long e) { return s + (e - s) / 2; }

long rmq(vector<long> arr, long start, long end)
{
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long n;
    cin >> n;
    vector<long> arr(n);
    for (long i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    long sum = 0;
    long request;
    cin >> request;

    for (long i = 0; i < request; i++)
    {
        long start, end;
        cin >> start >> end;
        for (long j = start; j <= end; j++)
        {
            sum += rmq(arr, start, end);
        }
    }
    cout << sum;

    return 0;
}

// This code is contributed by rathbhupendra
