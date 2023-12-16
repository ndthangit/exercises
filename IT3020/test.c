#include <stdio.h>
#include <math.h>
float findMin(float x[], int n){
    int i ;
    float min = x[0];
    for ( i = i; i < n; i++)
    {
        if (x[i]<min)
        {
           min =x[i];
        }
        
    }
    return min;
}
void nhapDaySo(float arr[], int n) {
    printf("Nhap vao day so: \n");
    for (int i = 0; i < n; i++) {
        printf("Nhap so thu %d: ", i+1);
        scanf("%f", &arr[i]);
    }
}

void sapXepDaySo(float arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (arr[i] > arr[j]) {
                float t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
    }
}

void inDaySo(float arr[], int n) {
    printf("Day so da sap xep: \n");
    for (int i = 0; i < n; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Nhap vao so phan tu cua day: ");
    scanf("%d", &n);

    float arr[n];
    nhapDaySo(arr, n);
    sapXepDaySo(arr, n);
    inDaySo(arr, n);
    return 0;
}
