/*bai 2.10 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

const int N_thangnd = 128;

struct Matrix {
    unsigned int mat[N_thangnd][N_thangnd];

    Matrix() {
        memset(mat, 0, sizeof mat);
    }
};

bool operator == (const Matrix &a_thangnd, const Matrix &b_thangnd) {
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    for (int i_thangnd = 0; i_thangnd < N_thangnd; ++i_thangnd) {
        for (int j_thangnd = 0; j_thangnd < N_thangnd; ++j_thangnd) {
            if (a_thangnd.mat[i_thangnd][j_thangnd] != b_thangnd.mat[i_thangnd][j_thangnd]) return false;
        }
    }
    return true;
}

Matrix multiply_naive(const Matrix &a_thangnd, const Matrix &b_thangnd) {
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    Matrix c_thangnd;
    for (int i_thangnd = 0; i_thangnd < N_thangnd; ++i_thangnd) {
        for (int j_thangnd = 0; j_thangnd < N_thangnd; ++j_thangnd) {
            for (int k_thangnd = 0; k_thangnd < N_thangnd; ++k_thangnd) {
                c_thangnd.mat[i_thangnd][j_thangnd] += a_thangnd.mat[i_thangnd][k_thangnd] * b_thangnd.mat[k_thangnd][j_thangnd];
            }
        }
    }
    return c_thangnd;
}

Matrix multiply_fast(const Matrix &a_thangnd, const Matrix &b_thangnd) {
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    Matrix c_thangnd;
    for (int i_thangnd = 0; i_thangnd < N_thangnd; ++i_thangnd) {
        for (int j_thangnd = 0; j_thangnd < N_thangnd; ++j_thangnd) {
            for (int k_thangnd = 0; k_thangnd < N_thangnd; ++k_thangnd) {
                c_thangnd.mat[i_thangnd][j_thangnd] += a_thangnd.mat[i_thangnd][k_thangnd] * b_thangnd.mat[k_thangnd][j_thangnd];
            }
        }
    }
    
    return c_thangnd;
}

Matrix gen_random_matrix() {
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    Matrix a_thangnd;
    for (int i_thangnd = 0; i_thangnd < N_thangnd; ++i_thangnd) {
        for (int j_thangnd = 0; j_thangnd < N_thangnd; ++j_thangnd) {
            a_thangnd.mat[i_thangnd][j_thangnd] = rand();
        }
    }
    return a_thangnd;
}

Matrix base_thangnd;

double benchmark(Matrix (*multiply_thangnd) (const Matrix&, const Matrix&), Matrix &result_thangnd) {
    const int NUM_TEST_thangnd = 10;
    const int NUM_ITER_thangnd = 64;
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/


    Matrix a_thangnd = base_thangnd;
    result_thangnd = a_thangnd;

    double taken_thangnd = 0;
    for (int t_thangnd = 0; t_thangnd < NUM_TEST_thangnd; ++t_thangnd) {
        clock_t start_thangnd = clock();
        for (int i_thangnd = 0; i_thangnd < NUM_ITER_thangnd; ++i_thangnd) {
            a_thangnd = multiply_thangnd(a_thangnd, result_thangnd);
            result_thangnd = multiply_thangnd(result_thangnd, a_thangnd);
        }
        clock_t finish_thangnd = clock();
        taken_thangnd += (double)(finish_thangnd - start_thangnd);
    }
    taken_thangnd /= NUM_TEST_thangnd;

    printf("Time: %.9f\n", taken_thangnd / CLOCKS_PER_SEC);
    return taken_thangnd;
}

int main() {
    base_thangnd = gen_random_matrix();
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    Matrix a_thangnd, b_thangnd;
    printf("Slow version\n");
    double slow_thangnd = benchmark(multiply_naive, a_thangnd);
    printf("Fast version\n");
    double fast_thangnd = benchmark(multiply_fast, b_thangnd);

    if (a_thangnd == b_thangnd) {
        printf("Correct answer! Your code is %.2f%% faster\n", slow_thangnd / fast_thangnd * 100.0);
    } else {
        printf("Wrong answer!\n");
    }
    return 0;
}
/*bai 2.10 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
