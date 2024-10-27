/*bai 1.1 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <stdio.h>
int main()
{
    int x_thangnd, y_thangnd, z_thangnd;
    int *ptr_thangnd;
    printf("Enter three integers: ");
    scanf("%d %d %d", &x_thangnd, &y_thangnd, &z_thangnd);
    printf("\nThe three integers are:\n");
    ptr_thangnd = &x_thangnd;
    printf("x = %d\n", *ptr_thangnd);

    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    ptr_thangnd = &y_thangnd;
    printf("y = %d\n", *ptr_thangnd);

    ptr_thangnd = &z_thangnd;
    printf("z = %d\n", *ptr_thangnd);

    return 0;
}
/*bai 1.1 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/