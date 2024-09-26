#include <bits/stdc++.h>
using namespace std;

long minVal(long x, long y) { return (x < y) ? x : y; }
long getMid(long s, long e) { return s + (e - s) / 2; }

long RMQUtil(long *st, long ss, long se, long qs, long qe, long index)
{

    if (qs <= ss && qe >= se)
        return st[index];

    if (se < qs || ss > qe)
        return INT_MAX;

    long mid = getMid(ss, se);
    return minVal(RMQUtil(st, ss, mid, qs, qe, 2 * index + 1),
                  RMQUtil(st, mid + 1, se, qs, qe, 2 * index + 2));
}

long RMQ(long *st, long n, long qs, long qe)
{
    if (qs < 0 || qe > n - 1 || qs > qe)
    {
        cout << "Invalid Input";
        return -1;
    }

    return RMQUtil(st, 0, n - 1, qs, qe, 0);
}

long constructSTUtil(long arr[], long ss, long se,
                     long *st, long si)
{
    if (ss == se)
    {
        st[si] = arr[ss];
        return arr[ss];
    }

    long mid = getMid(ss, se);
    st[si] = minVal(constructSTUtil(arr, ss, mid, st, si * 2 + 1),
                    constructSTUtil(arr, mid + 1, se, st, si * 2 + 2));
    return st[si];
}

long *constructST(long arr[], long n)
{
    long x = (long)(ceil(log2(n)));
    long max_size = 2 * (long)pow(2, x) - 1;
    long *st = new long[max_size];
    constructSTUtil(arr, 0, n - 1, st, 0);
    return st;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long n;
    cin >> n;
    long arr[n];
    for (long i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    long *st = constructST(arr, n);
    long sum = 0;
    long request;
    cin >> request;
    for (long i = 0; i < request; i++)
    {
        long qs, qe;
        cin >> qs >> qe;
        sum += RMQ(st, n, qs, qe);
    }
    cout << sum;
    return 0;
}
