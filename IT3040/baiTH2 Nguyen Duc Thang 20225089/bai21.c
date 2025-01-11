/*bai 2.1 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <stdio.h>
#include <math.h>

float get_hypotenuse(float x_thangnd, float y_thangnd)
{
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    return sqrt(x_thangnd * x_thangnd + y_thangnd * y_thangnd);
}

int main()
{
    float x_thangnd, y_thangnd;
    scanf("%f%f", &x_thangnd, &y_thangnd);

    float z_thangnd = get_hypotenuse(x_thangnd, y_thangnd);
    printf("z = %.2f\n", z_thangnd);

    return 0;
}
/*bai 2.1 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/