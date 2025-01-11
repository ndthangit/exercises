/*bai 3.5 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <iostream>
using namespace std;

int binom(int n, int k)
{
    if (k > n)
        return 0;
    if (k == 0)
        return 1;
    return binom(n - 1, k) + binom(n - 1, k - 1);
}

int binom2(int n, int k)
{

    // # Khử đệ quy
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241 */
    long long n_giaithua_thangnd = 1;
    long long nk_giaithua_thangnd = 1;
    long long k_giaithua_thangnd = 1;
    for (int i = 1; i <= n; i++)
    {
        n_giaithua_thangnd *= i;
        if (i <= k)
            k_giaithua_thangnd *= i;
        if (i <= n - k)
            nk_giaithua_thangnd *= i;
    }
    return n_giaithua_thangnd/(k_giaithua_thangnd*nk_giaithua_thangnd);
}

int main()
{
    int m;
    cin >> m;
    for (int n = 1; n <= m; ++n)
    {
        for (int k = 0; k <= n; ++k)
            printf("%d ", binom(n, k));
        printf("\n");
    }
    for (int n = 1; n <= m; ++n)
    {
        for (int k = 0; k <= n; ++k)
            printf("%d ", binom2(n, k));
        printf("\n");
    }
    return 0;
}
/*bai 3.5 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/