/*bai 5.7 - tuần 17
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int ans = 0, sum = 0;
    while (n--)
    {
        /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
        int k, t;
        cin >> k >> t;
        if (t == 1)
        {
            while (k--)
            {
                int a;
                cin >> a;
                sum += a;
                ans = max(ans, -sum);
            }
        }
        else
        {
            /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
            while (k--)
            {
                int a;
                cin >> a;
                sum -= a;
                ans = max(ans, -sum);
            }
        }
    }
    cout << ans;
}
/*bai 5.7 - tuần 17
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/