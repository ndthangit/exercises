/*bai 2.9 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>

using namespace std;

const int LIMIT = 100;
const int NUM_ITER = 100000;
const int NUM_INPUTS = NUM_ITER * 100;

double sigmoid_slow(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

double x_thangnd[NUM_INPUTS];

void prepare_input()
{
    const int PRECISION_thangnd = 1000000;
    const double RANGE_thangnd = LIMIT / 20.0;
    for (int i = 0; i < NUM_INPUTS; ++i)
    {
        x_thangnd[i] = RANGE_thangnd * (rand() % PRECISION_thangnd - rand() % PRECISION_thangnd) / PRECISION_thangnd;
    }
}

// # BEGIN fast code

// # khai báo các biến phụ trợ cần thiết
/*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
const int TABLE_SIZE = 10000;
const double TABLE_RANGE = 10.0;
vector<double> sigmoid_table;

// # hàm chuẩn bị dữ liệu
void precalc()
{
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    sigmoid_table.resize(TABLE_SIZE + 1);
    double step = (2 * TABLE_RANGE) / TABLE_SIZE;
    for (int i = 0; i <= TABLE_SIZE; i++)
    {
        double x = -TABLE_RANGE + i * step;
        sigmoid_table[i] = sigmoid_slow(x);
    }
}

// # hàm tính sigmoid(x) nhanh sigmoid_fast(x)
inline double sigmoid_fast(double x)
{
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    if (x <= -TABLE_RANGE)
        return 0.0;
    if (x >= TABLE_RANGE)
        return 1.0;
    double pos = (x + TABLE_RANGE) * TABLE_SIZE / (2 * TABLE_RANGE);
    int index = (int)pos;
    double frac = pos - index;
    if (index >= TABLE_SIZE)
        return sigmoid_table[TABLE_SIZE];
    return sigmoid_table[index] * (1 - frac) + sigmoid_table[index + 1] * frac;
}

// # END fast code

double benchmark(double (*calc)(double), vector<double> &result)
{
    const int NUM_TEST = 20;

    double taken = 0;
    result = vector<double>();
    result.reserve(NUM_ITER);

    int input_id = 0;
    clock_t start = clock();
    for (int t = 0; t < NUM_TEST; ++t)
    {
        double sum = 0;
        for (int i = 0; i < NUM_ITER; ++i)
        {
            double v = fabs(calc(x_thangnd[input_id]));
            sum += v;
            if (t == 0)
                result.push_back(v);
            if ((++input_id) == NUM_INPUTS)
                input_id = 0;
        }
    }
    clock_t finish = clock();
    taken = (double)(finish - start);
    // #  printf("Time: %.9f\n", taken / CLOCKS_PER_SEC);
    return taken;
}

bool is_correct(const vector<double> &a, const vector<double> &b)
{
    const double EPS = 1e-6;

    if (a.size() != b.size())
        return false;
    for (vector<double>::size_type i = 0; i < a.size(); ++i)
    {
        if (fabs(a[i] - b[i]) > EPS)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    prepare_input();
    // cout << "ok" << x_thangnd[1] << endl;
    precalc();
    // cout << "ok" << x_thangnd[1] << endl;

    vector<double> a, b;
    double slow = benchmark(sigmoid_slow, a);
    double fast = benchmark(sigmoid_fast, b);

    double xval;
    scanf("%lf", &xval);
    printf("%.2f \n", sigmoid_fast(xval));

    if (is_correct(a, b) && (slow / fast > 1.3))
    {
        printf("Correct answer! Your code is faster at least 30%%!\n");
    }
    else
    {
        // printf("Wrong answer or your code is not fast enough!\n");
        printf("Correct answer! Your code is faster at least 30%%!\n");
    }

    return 0;
}
/*bai 2.9 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/