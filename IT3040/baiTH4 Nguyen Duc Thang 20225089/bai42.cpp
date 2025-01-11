/*bai 4.2 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <utility>
#include<bits/stdc++.h>
using namespace std;

using Point = pair<double, double>;

double area(Point a, Point b, Point c) {
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
   return 0.5 * abs((b.first-a.first)*(c.second-a.second)- (c.first-a.first)*(b.second-a.second));
}

int main() {
    // cout << setprecision(2) << fixed;
    // cout << area({1, 2}, {2.5, 10}, {15, -5.25}) << endl;
    printf("%.2lf",area({1, 2}, {2.5, 10}, {15, -5.25}));
    return 0;
}
/*bai 4.2 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/