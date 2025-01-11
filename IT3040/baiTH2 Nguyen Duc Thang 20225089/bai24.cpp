/*bai 2.4 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <stdio.h>

template <class T>
T cube(T x_thangnd)
{
    // # trả về lập phương của x
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    return x_thangnd * x_thangnd * x_thangnd;
}

int main()
{
    int n_thangnd;
    double f_thangnd;
    scanf("%d %lf", &n_thangnd, &f_thangnd);

    printf("Int: %d\n", cube(n_thangnd));
    printf("Double: %.2lf\n", cube(f_thangnd));

    return 0;
}
/*bai 2.4 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
