/*bai 1.9 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    // khai báo 1 con trỏ mảng
    int *arr_thangnd;
    int n_thangnd;
    // nhập số phần tử của mảng
    printf("INPUT: ");
    scanf("%d", &n_thangnd);

    // cấp phát bộ nhớ cho mảng
    arr_thangnd = (int *)malloc(n_thangnd * sizeof(int));
    for (int i = 0; i < n_thangnd; i++)
        scanf("%d", arr_thangnd + i);
    // in ra các tập con
    printf("OUTPUT:\n");
    for (int start_thangd = 0; start_thangd < n_thangnd; start_thangd++)
    {
        // khai báo 2 biến chỉ vị trí bắt đầu và kết thúc của tập con
        int point_thangnd=start_thangd;
        int end_thangnd =start_thangd;
        // in ra tập con
        while (end_thangnd<n_thangnd)
        {
            printf("%d ",arr_thangnd[point_thangnd]);
            
            if(point_thangnd == end_thangnd){
                end_thangnd++;
                point_thangnd=start_thangd;
                printf("\n");
            }else
                point_thangnd++;
        }
        
    }
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    return 0;
}
/*bai 1.9 - tuần 8
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
