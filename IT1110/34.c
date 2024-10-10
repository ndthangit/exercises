#include <stdio.h>
#include<string.h>

int main()
{
    char str[] = "13*x^5+15*x^3-6*x^4";
    char *p=str;
    int arr[6], i = 0;
    for(int i=0;i<6;i++)
    {
        sscanf(p,"%*[^0-9]%d",&arr[i]);
        p =p+ strspn(p, "0123456789")-1;
       

    }
    // while (sscanf(p, "%d", &arr[i++])==1)
    // {
    //     p += strspn(p, "0123456789");
    //     p += strspn(p, "0123456789");
    // }
    for (int j = 0; j < 6; j++)
    {
        printf("%d ", arr[j]);
    }
    return 0;
}