#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    int i, j, n;
    struct sv
    {
        char hoten[30];
        char shsv[9];
        struct 
        {
            int ng,th,na;
        } ngaysinh;
        char tenlop[30];
        float dtdc;
        
    } ds[100], tg;
    i=0;
    while (i<100)
    {
        printf("\n vao ho so sinh vien thu %d",i+1);
        printf("\n ho va ten: "); fflush(stdin);
        gets(ds[i].hoten);
        if(ds[i].hoten[0]=='\0') break;
        printf("\n shsv     :");fflush(stdin);
        gets(ds[i].shsv);
        printf("\n sinh ngay :");
        scanf("%d",&ds[i].ngaysinh.ng);
        printf("\n sinh thang :");
        scanf("%d",&ds[i].ngaysinh.th);
        printf("\n sinh nam :");
        scanf("%d",&ds[i].ngaysinh.na);
        printf("\n ten lop   :");fflush(stdin);
        gets(ds[i].tenlop);
        printf("\n diem tdc :");
        scanf("%f",&ds[i].dtdc);
        i++;
    }
    n=1;
    printf("\n                                 DANH SACH SV                                             ");
    printf("\n------------------------------------------------------------------------------------------");
    printf("\n       SHSV      |         HO VA TEN         |      lop       |   NGAY SINH   |     TDC   \n");
    for (int  j = 0; j < i; j++)
    {
    printf("  %10s     |   %20s    |     %6s     |%4d/%3d/%5d |  %5f     \n",ds[j].shsv,ds[j].hoten,ds[j].tenlop,ds[j].ngaysinh.ng,ds[j].ngaysinh.th,ds[j].ngaysinh.na,ds[j].dtdc );    
    } 
    printf("------------------------------------------------------------------------------------------");
    // for (int j = 0; j <i; j++)
    // {
    // printf("\n %2d             | %9s                       | %20s           | %10s  | %02d/%02d/%4d | %8.2f ",
    // n, ds[j].shsv, ds[j].hoten, ds[j].tenlop, ds[j].ngaysinh.ng, ds[j].ngaysinh.th, ds[j].ngaysinh.na, ds[j].dtdc);
    //     n++;
    //}
  
}