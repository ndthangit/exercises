/*bai 3.6 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <iostream>
using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int gcd2(int a, int b)
{

    // # Khử đệ quy
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    while (b != 0 && a != 0)
    {
        if (a > b)
            a = a % b;
        else
            b = b % a;
    }
    return a ? a : b;
}

int main()
{
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl
         << gcd2(a, b);
    return 0;
}
/*bai 3.6 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/