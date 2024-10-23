#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

char *ListStudent[300] ;
int num_students = 0;

void printStudent() {
    printf("|    Ten     |\n");
    for (int i = 0; i < num_students; i++) {
        printf("| %s |\n", ListStudent[i]);
    }
    printf("\nPress any key to continue...");
    getch();
}

void freelist() {
    for (int i = 0; i < num_students; i++) {
        free(ListStudent[i]);
    }
    free(ListStudent);
}

void bosung() {

    char buffer[100];

    fflush(stdin);

    printf("Enter Ten: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    ListStudent[num_students] = (char *)malloc(strlen(buffer) + 1);
    strcpy(ListStudent[num_students], buffer);

    num_students++;
    fflush(stdin);
}

void xoa(char *ten) {
    int found = 0;

    for (int i = 0; i < num_students; i++) {
        if (strcmp(ListStudent[i], ten) == 0) {
            free(ListStudent[i]);
            for (int j = i; j < num_students - 1; j++) {
                ListStudent[j] = ListStudent[j + 1];
            }
            num_students--;
            found = 1;

            printf("Da xoa sinh vien co ten %s\n", ten);
            break;
        }
    }

    if (!found) {
        printf("Khong tim thay sinh vien voi ten %s\n", ten);
    }

    printf("\nPress any key to continue...");
    getch();
}

void sapxep() {
    char *temp;
    for (int i = 0; i < num_students - 1; i++) {
        for (int j = 0; j < num_students - i - 1; j++) {
            if (strcmp(ListStudent[j], ListStudent[j + 1]) > 0) {
                temp = ListStudent[j];
                ListStudent[j] = ListStudent[j + 1];
                ListStudent[j + 1] = temp;
            }
        }
    }
    printf("Da sap xep danh sach theo ten.\n");

    printf("\nPress any key to continue...");
    getch();
}

int main() {
    char ch;
    while (1) {
        system("cls");
        printf("\n");
        printf("\n          CHUONG TRINH QUAN LY SINH VIEN");
        printf("\n");
        printf("\n              1. Bo sung danh sach ");
        printf("\n              2. Sap xep danh sach ");
        printf("\n              3. Xoa sinh vien ");
        printf("\n              4. In danh sach ");
        printf("\n      Bam 1,2,3 de chon, fim khac de ket thuc \n");

        scanf(" %c", &ch);

        if (ch == '1') {
            bosung();
        } else if (ch == '2') {
            sapxep();
        } else if (ch == '3') {
            fflush(stdin);
            char ten[100];
            printf("Enter Ten: ");
            fgets(ten, sizeof(ten), stdin);
            ten[strcspn(ten, "\n")] = 0;
            xoa(ten);
        } else if (ch == '4') {
            printStudent();
        } else {
            break;
        }
    }

    freelist();
    return 0;
}
