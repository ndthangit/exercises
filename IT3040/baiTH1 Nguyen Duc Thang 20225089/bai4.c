/*bai 1.4 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

#include <stdio.h>
int counteven(int *arr_thangnd, int size_thangnd)
{
    int count_thangnd = 0;

    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    for (int i = 0; i < size_thangnd; i++)
        if (arr_thangnd[i] % 2 == 0) count_thangnd++;
    return count_thangnd;
}
int main()
{
    int a_thangnd[7] = {13, -355, 235, 47, 67, 943, 1222};
    printf("Number of even elements in the array: %d\n", counteven(a_thangnd, 7));
    return 0;
}
/*bai 1.4 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/