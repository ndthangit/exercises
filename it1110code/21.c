#include <stdio.h>
#include <string.h>

int main() {
    char str[] = " 13*x^5+   15*x^8-16*x^4";
    int arr[6];
    int i;
    char *p = str;

    for (i = 0; i <6; ) {
        sscanf(p, "%d", &arr[i]);
        i++;
        p = strchr(p, '^') + 1;
        sscanf(p, "%d", &arr[i]);
        p = strchr(p, ' ') + 1;
        i++;
    }

    printf("Cac gia tri trong mang la:\n");
    for (i = 0; i < 6; i++) {
        printf("%d\n", arr[i]);
    }

    return 0;
}