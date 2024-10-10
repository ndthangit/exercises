#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    int s[1000];

    // for (int i = 0; i < 5; i++) {
    //     // printf("Nhập dòng thứ %d: ", i+1);
    //     s[i]= i++;
    //     printf("ok");
    // }
    int x = 10;
    // int *ptr = &x;
    // float *fptr = (float*)ptr;
    // *fptr = 20.0;
    // printf("Value of x is %d\n", x);                                 // Output: 10
    // printf("Address of x is %lu\n", (unsigned long int)&x);          // Output: địa chỉ của x
    // printf("Value of pointer ptr is %lu\n", (unsigned long int)ptr); // Output: địa chỉ của x
    // printf("Ptr pointing value is %d\n", ptr);                      // Output: 10
    // printf("Ptr pointing value is %f\n", *fptr);                      // Output: 10
    int* ptr = (int*)malloc(5 * sizeof(int)); // Cấp phát vùng nhớ đủ cho 5 số nguyên
    printf("Address of dynamically allocated memory: %lu\n", (unsigned long int*)ptr);
    for (int i = 0; i < 5; i++)
    {
        printf(" %lu\n", ptr[i]);
    }
    ptr = (int*)realloc(ptr, 10 * sizeof(int));
    printf("Address of dynamically reallocated memory: %lu\n", (unsigned long int*)ptr);
    for (int i = 0; i < 10; i++)
    {
        printf(" %lu\n", ptr[i]);
    }
    int* ptr1 = (int*)calloc(5, sizeof(int)); // Cấp phát vùng nhớ cho 5 số nguyên và khởi tạo tất cả về 0
    printf("Address of dynamically allocated memory: %lu\n", (unsigned long int*)ptr1);
    for (int i = 0; i < 5; i++)
    {
        printf(" %lu\n", ptr1[i]);
    }
    
    
    return 0;
}