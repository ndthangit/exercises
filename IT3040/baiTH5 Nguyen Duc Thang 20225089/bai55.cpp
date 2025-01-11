/*bai 5.5 - tuần 17
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    bool found = false;
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    while (n--)
    {
        int a;
        cin >> a;
        if ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0))
            cout << "Yes";
        return 0;
    }
    cout << "No";
}
/*bai 5.5 - tuần 17
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/