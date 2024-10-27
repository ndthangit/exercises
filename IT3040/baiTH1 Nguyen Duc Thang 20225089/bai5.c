/*bai 1.5 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <stdio.h>

double *maximum(double *a_thangnd, int size_thangnd)
{
    double *max_thangnd;
    max_thangnd = a_thangnd;
    if (a_thangnd == NULL)
        return NULL;
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    for (int i = 0; i < size_thangnd; i++) (*max_thangnd < a_thangnd[i]) ? max_thangnd = &a_thangnd[i] : max_thangnd;
    return max_thangnd;
}
int main()
{
    double a_thangnd[7] = {13.5, -355.2, 235.1, 47.3, 67.4, 943.5, 1222.6};
    double *max_thangnd = maximum(a_thangnd, 7);
    if (max_thangnd != NULL)
        printf("The maximum value in the array is: %f\n", *max_thangnd);
    else
        printf("The array is empty.\n");
    return 0;
}
/*bai 1.5 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
