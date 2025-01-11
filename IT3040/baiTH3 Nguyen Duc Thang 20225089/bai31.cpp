/*bai 3.1 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <stdio.h>
#include <math.h>

int lucas(int n_thangnd)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    if (n_thangnd == 0)
        return 2;
    if (n_thangnd == 1)
        return 1;
    return lucas(n_thangnd - 1) + lucas(n_thangnd - 2);
}

int main()
{
    int n_thangnd;
    scanf("%d",&n_thangnd);
    printf("%d", lucas(n_thangnd));
}
/*bai 3.1 - tuần 13
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/