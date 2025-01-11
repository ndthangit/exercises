/*bai 2.6 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <stdio.h>

void print(int n_thangnd) {
    printf("n=%d\n", n_thangnd);
}

int mul3plus1(int n_thangnd) {
    return n_thangnd * 3 + 1;
}

int div2(int n_thangnd) {
    return n_thangnd / 2;
}

// khai báo các tham số cho các con trỏ hàm odd_thangnd, even_thangnd và output_thangnd
void simulate(int n_thangnd, /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/ 
                      int (*odd_thangnd)(int), 
                      int (*even_thangnd)(int), 
                      void (*output_thangnd)(int)) {
    (*output_thangnd)(n_thangnd);
    if (n_thangnd == 1) return;
    if (n_thangnd % 2 == 0) {
        n_thangnd = (*even_thangnd)(n_thangnd);
    } else {
        n_thangnd = (*odd_thangnd)(n_thangnd);
    }
    simulate(n_thangnd, odd_thangnd, even_thangnd, output_thangnd);
}

int main() {
    int (*odd_thangnd)(int) = NULL;
    int (*even_thangnd)(int) = NULL;

    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    odd_thangnd = mul3plus1;
    even_thangnd = div2;
    

    int n_thangnd;
    scanf("%d", &n_thangnd);
    simulate(n_thangnd, odd_thangnd, even_thangnd, print);

    return 0;
}
/*bai 2.6 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
