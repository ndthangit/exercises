
/*bai 1.3 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <stdio.h>
int main()
{
    int x_thangnd, y_thangnd, z_thangnd;
    int *ptr_thangnd;
    scanf("%d %d %d", &x_thangnd, &y_thangnd, &z_thangnd);
    printf("Here are the values of x, y, and z:\n");
    printf("%d %d %d\n", x_thangnd, y_thangnd, z_thangnd);
    
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    ptr_thangnd = &x_thangnd;
    *ptr_thangnd += 100;
    ptr_thangnd = &y_thangnd;
    *ptr_thangnd += 100;
    ptr_thangnd = &z_thangnd;
    *ptr_thangnd += 100;

    printf("Once again, here are the values of x, y, and z:\n");
    printf("%d %d %d\n", x_thangnd, y_thangnd, z_thangnd);
    return 0;
}
/*bai 1.3 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/