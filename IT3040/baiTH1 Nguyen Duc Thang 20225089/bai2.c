/*bai 1.2 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <stdio.h>
int main()
{
    int a_thangnd[7] = {13, -355, 235, 47, 67, 943, 1222};
    printf("address of first five elements in memory.\n");
    for (int i = 0; i < 5; i++)
        printf("\t\t   a[%d] ", i);
    printf("\n");

    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    for (int i = 0; i < 5; i++)
        printf("\t%p", &a_thangnd[i]);
    return 0;
}
/*bai 1.2 tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
