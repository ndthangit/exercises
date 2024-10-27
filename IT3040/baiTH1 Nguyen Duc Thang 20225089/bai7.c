/*bai 1.7 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <stdio.h>
#include <stdlib.h>

int *a_thangnd;
int n_thangnd, tmp_thangnd;
int main()
{
    printf("Enter the number of elements: ");
    scanf("%d", &n_thangnd);

    // #Allocate memory
    a_thangnd = (int *)malloc(n_thangnd * sizeof(int));

    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    for (int i = 0; i < n_thangnd; i++)
        scanf("%d", a_thangnd + i);

    printf("The input array is: \n");
    for (int i = 0; i < n_thangnd; i++)
        printf("%d ", *(a_thangnd + i));
    printf("\n");

    // #Sort array
    for (int i = 0; i < n_thangnd - 1; i++)
    {
        for (int j = i + 1; j < n_thangnd; j++)
        {
            if (a_thangnd[i] > a_thangnd[j])
            {
                // đổi vị trí 2 phần tử
                int tmp_thangnd;
                tmp_thangnd = a_thangnd[i];
                a_thangnd[i] = a_thangnd[j];
                a_thangnd[j] = tmp_thangnd;
            }
        }
    }

    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    printf("The sorted array is: \n");
    for (int i = 0; i < n_thangnd; i++)
        printf("%d ", *(a_thangnd + i));
    printf("\n");
    free(a_thangnd);
    return 0;
}
/*bai 1.7 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
