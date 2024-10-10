#include <stdio.h>
#include <stdlib.h>
#include <string.h>    
int i,j,n=0;
struct SV {
     char hoten[30];
     char shsv[9]; 
     struct {
         int ng,th,na; } ngaysinh;
     char tenlop[30];
     float dtdc;
  } ds[1000],tg; 

void bosung() {
  i=n;
  while (i<1000) {
    printf("\n Vao ho so sv thu %d ",i+1);
    printf("\n Ho ten : "); fflush(stdin);
    gets(ds[i].hoten);
    if (ds[i].hoten[0]=='\0') break;
    printf("\n SHSV   : "); fflush(stdin);
    gets(ds[i].shsv);
    printf("\n Sinh ngay : "); 
    scanf("%d",&ds[i].ngaysinh.ng); 
    printf("\n Sinh thang : "); 
    scanf("%d",&ds[i].ngaysinh.th); 
    printf("\n Sinh nam : "); 
    scanf("%d",&ds[i].ngaysinh.na);
    printf("\n tenlop   : "); fflush(stdin);
    gets(ds[i].tenlop);
    printf("\n diem TDC : "); 
    scanf("%f",&ds[i].dtdc);
    i++;
  }
  n=i; 
}

void sapxep() {
   for(i=0;i<n-1;i++)
   for(j=i+1;j<n;j++)
    if (strcmp(ds[i].hoten,ds[j].hoten)>0) {
      tg=ds[i];
      ds[i]=ds[j];
	  ds[j]=tg;
    }
   printf("\n Da sap xep xong !");
   getch();
}
void inds() {
printf("\n         DANH SACH SV");
  printf("\n----------------------------------------------------------");
  printf("\n|  SHSV  |          Ho va ten           |Ngay sinh |D TDC|");
  printf("\n|--------|------------------------------|----------|-----|");
  for(i=0;i<n;i++) 
    printf("\n|%-8s|%-30s|%2d/%2d/%4d|%5.2f|",ds[i].shsv,ds[i].hoten,ds[i].ngaysinh.ng,ds[i].ngaysinh.th,ds[i].ngaysinh.na,ds[i].dtdc);
  printf("\n|--------|------------------------------|----------|-----|");
  getch();
}

int main() {
  char ch;
  while(1) {

    system("cls");
    printf("\n");
    printf("\n          CHUONG TRINH QUAN LY SINH VIEN");
    printf("\n");
    printf("\n              1. Bo sung danh sach ");
    printf("\n              2. Sap xep danh sach ");
    printf("\n              3. In danh sach ");
    printf("\n                 Bam 1,2,3 de chon, fim khac de ket thuc ");
    fflush(stdin);
    ch=getch();
    if (ch=='1') bosung();
    else if (ch=='2') sapxep();
    else if ( ch=='3') inds();
    else break;
  }
}