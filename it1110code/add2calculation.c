#include<stdio.h>
#include<string.h>
#include <stdlib.h>

int main(){
    char line1[10001];
    printf("nhap phep tinh dau tien");
    fgets(line1,10001,stdin);
    
    char line2[10001];
    printf("nhap phep tinh thu hai");
    fgets(line2,10001,stdin);
    
    // đếm dòng 1
    int demLine1=0;
    for(int i=0;i<strlen(line1);i++)    
    {
        if(line1[i]=='x') demLine1++;
    }
    int heSoLine1[demLine1], soMuLine1[demLine1]; 
    char *pterLine1 =line1;
    for(int i=0; i<demLine1;)
    {
        sscanf(pterLine1,"%d",&heSoLine1[i]);
        pterLine1 = strchr(pterLine1, '^') + 1;
        sscanf(pterLine1,"%d",&soMuLine1[i]);
        pterLine1++;
        i++;
    }
    //test
    // printf("he so dong 1\n");
    // for (int i = 0; i < demLine1; i++)
    // {
    //     printf("he so %d | so mu %d\n", heSoLine1[i],soMuLine1[i]);
    // }
    
    
    // đếm dòng 2
    int demLine2=0;
    for(int i=0;i<strlen(line2);i++)    
    {
        if(line2[i]=='x') demLine2++;
    }
    int heSoLine2[demLine2], soMuLine2[demLine2]; 
    char *pterLine2 =line2;
    for(int i=0; i<demLine2;)
    {
        sscanf(pterLine2,"%d",&heSoLine2[i]);
        pterLine2 = strchr(pterLine2, '^') + 1;
        sscanf(pterLine2,"%d",&soMuLine2[i]);
        pterLine2++;
        i++;
    }
    // test
    // printf("he so dong 2\n");
    // for (int i = 0; i < demLine2; i++)
    // {
    //     printf("he so %d | so mu %d\n", heSoLine2[i],soMuLine2[i]);
    // }
    //tính toán
    int kpHeSo[10001],kpSoMu[10001];
    for(int i=0;i<10001;i++)
    {
        kpHeSo[i]=0;
        kpSoMu[i]=-1;
    }
    //test
    // printf("next\n");
    // for(int i=0;i<11;i++)
    // {
    //     printf("he so kp %d | so mu kp %d\n",kpHeSo[i],kpSoMu[i]);
    // }
    for(int i=0;i<demLine1;i++)
    {
        // printf(" he so 1: %d\n",heSoLine1[i]);
        // printf("so mu 1:  %d\n",soMuLine1[i]);
        kpSoMu[soMuLine1[i]]=soMuLine1[i];
        kpHeSo[soMuLine1[i]]=heSoLine1[i];
    }    
    //test
    // printf("next\n");
    // for(int i=0;i<11;i++)
    // {
    //     printf("he so kp %d | so mu kp %d\n",kpHeSo[i],kpSoMu[i]);
    // }
    for(int i=0;i<demLine2;i++)
    {
        // printf(" he so 2: %d\n",heSoLine2[i]);
        // printf("so mu 2:  %d\n",soMuLine2[i]);
        kpSoMu[soMuLine2[i]]=soMuLine2[i];
        kpHeSo[soMuLine2[i]]=heSoLine2[i];
    }    
    //test
    // printf("next\n");
    // for(int i=0;i<11;i++)
    // {
    //     printf("he so kp %d | so mu kp %d\n",kpHeSo[i],kpSoMu[i]);
    // }
    for(int i=0;i<demLine1;i++)
    {
        for (int j = 0; j < demLine2; j++)
        {
           if(soMuLine1[i]==soMuLine2[j]) 
           {
                kpSoMu[soMuLine1[i]]=soMuLine1[i];
                kpHeSo[soMuLine1[i]]=heSoLine1[i]+heSoLine2[j];
           }
        }
      
    }
    //test
    // printf("next\n");
    // for(int i=0;i<11;i++)
    // {
    //     printf("he so kp %d | so mu kp %d\n",kpHeSo[i],kpSoMu[i]);
    // }
    
    for(int i=0; i<10001;i++)
    {
        if(kpHeSo[i]!=0)
        {
            printf("+%d*x^%d",kpHeSo[i],kpSoMu[i]);
        }
    }
    

    return 0;
}
