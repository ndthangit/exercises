/*bai 5.1 - tuần 17
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <stdio.h>
int x[100], mark[100], n;
void print_thangnd()
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    for (int i = 1; i <= n; ++i)
        printf("%d ", x[i]);
    printf("\n");
}
void process(int i)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    if (i > n)
    {
        print_thangnd();
        return;
    }
    for (int j = 1; j <= n; ++j)
        if (!mark[j])
        {
            mark[j] = 1;
            x[i] = j;
            process(i + 1);
            mark[j] = 0;
        }
}
int main()
{
    n = 5;
    process(1);
    return 0;
}
/*bai 5.1 - tuần 17
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/