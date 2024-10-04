#include <stdio.h>

int main() {
    char s[1000];
    int i, j;

    for (i = 0; i < 5; i++) {
        // printf("Nhập dòng thứ %d: ", i+1);
        fgets(s, sizeof(s), stdin);

        printf("ASCII  %d:\n", i+1);
        for (j = 0; s[j] != '\0'; j++) {
            printf("%c: %d\n", s[j], s[j]);
        }
    }

    return 0;
}