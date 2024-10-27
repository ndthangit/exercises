/*bai 1.10 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

#include <stdio.h>
#include <stdlib.h>

int **taoMaTran(int n_thangnd)
{
    // khởi tạo và cấp phất bộ nhớ cho ma trận cỡ n*n
    int **arr_thangnd = (int **)malloc(n_thangnd * sizeof(int *));
    for (int i = 0; i < n_thangnd; i++)
    {
        arr_thangnd[i] = (int *)malloc(n_thangnd * sizeof(int));
    }

    // nhập giá trị cho ma trận
    for (int i = 0; i < n_thangnd; i++)
    {
        for (int j = 0; j < n_thangnd; j++)
        {
            scanf("%d", &arr_thangnd[i][j]);
        }
    }
    return arr_thangnd;
}
void xoaMaTran( int ** arr_thangnd, int n_thangnd)
{
    // giải phóng bộ nhớ của ma trận
    for (int i = 0; i < n_thangnd; i++)
    {
        free(arr_thangnd[i]);
    }
    free(arr_thangnd);
}
void tongHaiMaTran(int **arr1_thangnd,int **arr2_thangnd, int n_thangnd)
{    
    // in ra ma trận tổng
    for (int i = 0; i < n_thangnd; i++)
    {
        for (int j = 0; j < n_thangnd; j++)
        {
            printf("%d ", arr1_thangnd[i][j] + arr2_thangnd[i][j]);
        }
        printf("\n");
    }
}

void tichHaiMaTran( int ** arr1_thangnd, int ** arr2_thangnd, int n_thangnd){
    
    // tính tích 2 ma trận
    for (int i = 0; i < n_thangnd; i++)
    {
        for (int j = 0; j < n_thangnd; j++)
        {
            // tạo 1 biến lưu giá trị của phần tử thứ i,j của ma trận kết quả
            int phanTuThuIJ = 0;
            for (int k = 0; k < n_thangnd; k++)
            {
                phanTuThuIJ += arr1_thangnd[i][k] * arr2_thangnd[k][j];
            }
            printf("%d ", phanTuThuIJ);
        }
        printf("\n");
    }
}

int main()
{
    printf("INPUT: ");
    // khai báo và nhập kích thước các ma trận
    int n_thangnd;
    scanf("%d", &n_thangnd);
    // tạo 2 ma trận cỡ n*n
    int **arr1_thangnd = taoMaTran(n_thangnd);
    int **arr2_thangnd = taoMaTran( n_thangnd);

    printf("OUTPUT:\n");
    
    // tính tổng 2 ma trận
    tongHaiMaTran(arr1_thangnd, arr2_thangnd, n_thangnd);
    // tính tích 2 ma trận
    tichHaiMaTran(arr1_thangnd, arr2_thangnd, n_thangnd);

    // giải phóng bộ nhớ
    xoaMaTran(arr1_thangnd, n_thangnd);
    xoaMaTran(arr2_thangnd, n_thangnd);


    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    
    return 0;
}
/*bai 1.10 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
