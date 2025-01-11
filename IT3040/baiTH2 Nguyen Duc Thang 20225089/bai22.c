/*bai 2.2 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <stdio.h>

void rotate(int *x_thangnd , int *y_thangnd, int *z_thangnd)
{
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    // Viết hàm hoán vị vòng tròn 3 biến a, b, c. Sau khi thực hiện hàm, các biến a, b, c tương ứng nhận các giá trị mới b, c, a.
    int temp = *x_thangnd;
    *x_thangnd = *y_thangnd;
    *y_thangnd = *z_thangnd;
    *z_thangnd = temp;

}

int main()
{
    int x_thangnd, y_thangnd, z_thangnd;

    // # Nhập 3 số nguyên
    scanf("%d%d%d", &x_thangnd, &y_thangnd, &z_thangnd);

    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    printf("Before: %d, %d, %d\n", x_thangnd, y_thangnd, z_thangnd);
    rotate(&x_thangnd, &y_thangnd, &z_thangnd);
    printf("After: %d, %d, %d\n", x_thangnd, y_thangnd, z_thangnd);

    return 0;
}
/*bai 2.2 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/