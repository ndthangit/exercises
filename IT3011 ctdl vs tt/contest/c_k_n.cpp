#include <iostream>
#include <math.h>

using namespace std;

long long giaithua(long number)
{
    if (number == 1 || number == 0)
        return 1;
    else
        return number * giaithua(number - 1);
}
int main()
{

    long k, n;
    cin >> k >> n;
    // cout<< giaithua(10)<< endl;
    cout << giaithua(n) / (giaithua(k) * giaithua(n - k));
    return 0;
}