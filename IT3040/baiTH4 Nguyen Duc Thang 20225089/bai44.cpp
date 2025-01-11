/*bai 4.4 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
void print_vector(const vector<int> &a)
{
    for (int v : a)
        cout << v << ' ';
    cout << endl;
}

void delete_even(vector<int> &a)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] % 2 == 0) {
            a.erase(a.begin() + i);
        }
    }
}

void sort_decrease(vector<int> &a)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    sort(a.begin(), a.end(), [](const int &a, const int &b)
         { return a > b; });
}

vector<int> merge_vectors(const vector<int> &a, const vector<int> &b)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    vector<int> sum;
    for (auto i : a)
        sum.push_back(i);
    for (auto i : b)
        sum.push_back(i);
    sort_decrease(sum);
    return sum;
}

int main()
{
    int m, n, u;
    std::vector<int> a, b;

    std::cin >> m >> n;
    for (int i = 0; i < m; i++)
    {
        std::cin >> u;
        a.push_back(u);
    }
    for (int i = 0; i < n; i++)
    {
        std::cin >> u;
        b.push_back(u);
    }

    delete_even(a);
    cout << "Odd elements of a: ";
    print_vector(a);

    delete_even(b);
    cout << "Odd elements of b: ";
    print_vector(b);

    sort_decrease(a);
    cout << "Decreasingly sorted a: ";
    print_vector(a);

    sort_decrease(b);
    cout << "Decreasingly sorted b: ";
    print_vector(b);

    vector<int> c = merge_vectors(a, b);
    cout << "Decreasingly sorted c: ";
    print_vector(c);

    return 0;
}
/*bai 4.4 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
