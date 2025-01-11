/*bai 5.6 - tuần 17
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <bits/stdc++.h>
using namespace std;

char cal(double a)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    if (a < 4)
        return 'F';
    if (a < 5.5)
        return 'D';
    if (a < 7)
        return 'C';
    if (a < 8.5)
        return 'B';
    return 'A';
}

int main()
{
    int n;
    cin >> n;
    int A = 0, B = 0, C = 0, D = 0, F = 0;
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    while (n--)
    {
        int a;
        cin >> a;
        char calA = cal(a);
        if (calA == 'A')
            ++A;
        if (calA == 'B')
            ++B;
        if (calA == 'C')
            ++C;
        if (calA == 'D')
            ++D;
        if (calA == 'F')
            ++F;
    }
    cout << A << " " << B << " " << C << " " << D << " " << F;
}
/*bai 5.6 - tuần 17
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/