/*bai 2.3 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <iostream>
using namespace std;

// # Viết hàm get_value
/*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
int get_value(int x_thangnd, int a_thangnd = 2, int b_thangnd = 1, int c_thangnd = 0)
{
    return a_thangnd * x_thangnd * x_thangnd + b_thangnd * x_thangnd + c_thangnd;
}

int main()
{
    int x_thangnd;
    scanf("%d", &x_thangnd);

    int a_thangnd = 2; // # giá trị mặc định của a
    int b_thangnd = 1; // # giá trị mặc định của b
    int c_thangnd = 0; // # giá trị mặc định của c

    // # Nhập 3 số nguyên a, b, c từ bàn phím
    scanf("%d%d%d", &a_thangnd, &b_thangnd, &c_thangnd);

    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    printf("a=2, b=1, c=0: %d\n", get_value(x_thangnd));
    printf("a=%d, b=1, c=0: %d\n", a_thangnd, get_value(x_thangnd, a_thangnd));
    printf("a=%d, b=%d, c=0: %d\n", a_thangnd, b_thangnd, get_value(x_thangnd, a_thangnd, b_thangnd));
    printf("a=%d, b=%d, c=%d: %d\n", a_thangnd, b_thangnd, c_thangnd, get_value(x_thangnd, a_thangnd, b_thangnd, c_thangnd));

    return 0;
}
/*bai 2.3 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/