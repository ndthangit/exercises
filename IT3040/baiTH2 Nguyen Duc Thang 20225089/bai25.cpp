/*bai 2.5 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <iostream>
#include <ostream>
#include <math.h>
#include <iomanip> 

using namespace std;

struct Complex {
    double real;
    double imag;
};

Complex operator + (Complex a_thangnd, Complex b_thangnd) {
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    return {a_thangnd.real + b_thangnd.real, a_thangnd.imag + b_thangnd.imag};
}

Complex operator - (Complex a_thangnd, Complex b_thangnd) {
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    return {a_thangnd.real - b_thangnd.real, a_thangnd.imag - b_thangnd.imag};
}

Complex operator * (Complex a_thangnd, Complex b_thangnd) {
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    return {a_thangnd.real * b_thangnd.real - a_thangnd.imag * b_thangnd.imag, a_thangnd.real * b_thangnd.imag + a_thangnd.imag * b_thangnd.real};
}

Complex operator / (Complex a_thangnd, Complex b_thangnd) {
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    return {(a_thangnd.real * b_thangnd.real + a_thangnd.imag * b_thangnd.imag) / (b_thangnd.real * b_thangnd.real + b_thangnd.imag * b_thangnd.imag), (a_thangnd.imag * b_thangnd.real - a_thangnd.real * b_thangnd.imag) / (b_thangnd.real * b_thangnd.real + b_thangnd.imag * b_thangnd.imag)};
}

ostream& operator << (ostream& out, const Complex &a) {
    out << '(' << std::setprecision(2) << a.real << (a.imag >= 0 ? '+' : '-') << std::setprecision(2) << fabs(a.imag) << 'i' << ')';
    return out;
}

int main() {
    double real_a_thangnd, real_b_thangnd, img_a_thangnd, img_b_thangnd;
    cin >> real_a_thangnd >> img_a_thangnd;
    cin >> real_b_thangnd >> img_b_thangnd;
    
    Complex a{real_a_thangnd, img_a_thangnd};
    Complex b{real_b_thangnd, img_b_thangnd};
    
    cout << a << " + " << b << " = " << a + b << endl;
    cout << a << " - " << b << " = " << a - b << endl;
    cout << a << " * " << b << " = " << a * b << endl;
    cout << a << " / " << b << " = " << a / b << endl;
    
    return 0;
}
/*bai 2.5 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/