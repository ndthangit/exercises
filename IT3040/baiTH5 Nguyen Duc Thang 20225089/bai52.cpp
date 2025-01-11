/*bai 5.2 - tuần 17
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <iostream>
using namespace std;

int n, M, m[100], v[100];
int x[100], best, sumV, sumM, all[100];

void init()
{
    for (int i = n; i >= 1; --i)
    {
        all[i] = all[i + 1] + v[i];
    }
}

void print()
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    cout << best;
}

void process(int i)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    if (sumV + all[i] <= best || sumM > M)
        return;
    if (i > n)
    {
        best = sumV;
        return;
    }
    process(i + 1);
    sumM += m[i];
    sumV += v[i];
    process(i + 1);
    sumM -= m[i];
    sumV -= v[i];
}

int main()
{
    cin >> n >> M;
    for (int i = 1; i <= n; ++i)
        cin >> m[i] >> v[i];
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    init();
    process(1);
    print();
    return 0;
}
/*bai 5.2 - tuần 17
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
