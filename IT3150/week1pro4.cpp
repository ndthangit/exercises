#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    int n;
    cin >> n;
    long sum =0;
    for (int i = 0; i < n; i++)
    {
        long x;
        cin >> x;
        sum += x;
    }
    cout << sum << endl;

    return 0;
}