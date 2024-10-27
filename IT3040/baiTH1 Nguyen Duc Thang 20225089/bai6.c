/*bai 1.6 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <stdio.h>
void reversearray(int arr_thangnd[], int size_thangnd)
{
    int l_thangnd = 0, r_thangnd = size_thangnd - 1, tmp_thangnd;
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    while (l_thangnd < r_thangnd)
    {
        // đổi vị trí 2 phần tử trong mảng
        tmp_thangnd = arr_thangnd[l_thangnd];
        arr_thangnd[l_thangnd] = arr_thangnd[r_thangnd];
        arr_thangnd[r_thangnd] = tmp_thangnd;
        l_thangnd++;
        r_thangnd--;
    }
}
void ptr_reversearray(int *arr_thangnd, int size_thangnd)
{
    int l_thangnd = 0, r_thangnd = size_thangnd - 1, tmp_thangnd;
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    while (l_thangnd < r_thangnd)
    {
        // đổi vị trí 2 phần tử trong mảng
        tmp_thangnd = *(arr_thangnd + l_thangnd);
        *(arr_thangnd + l_thangnd) = *(arr_thangnd + r_thangnd);
        *(arr_thangnd + r_thangnd) = tmp_thangnd;
        l_thangnd++;
        r_thangnd--;
    }
}
int main()
{
    int arr_thangnd[5] = {9, -1, 4, 5, 7};
    printf("Original array: ");
    for (int i = 0; i < 5; i++)
        printf("%d ", arr_thangnd[i]);
    printf("\n");
    reversearray(arr_thangnd, 5);
    printf("Reversed array: ");
    for (int i = 0; i < 5; i++)
        printf("%d ", arr_thangnd[i]);
    printf("\n");
    ptr_reversearray(arr_thangnd, 5);
    printf("Reversed array: ");
    for (int i = 0; i < 5; i++)
        printf("%d ", arr_thangnd[i]);
    printf("\n");

    return 0;
}
/*bai 1.6 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
