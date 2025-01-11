/*bai 2.11 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <bits/stdc++.h>
using namespace std;

typedef complex<double> base;
typedef vector<base> vb;

void input(ifstream &fin_thangnd, int &n_thangnd, int &m_thangnd, vb &x_thangnd, vb &y_thangnd)
{
    fin_thangnd >> n_thangnd;
    for (int i = 0; i <= n_thangnd; i++)
    {
        int tmp_thangnd;
        fin_thangnd >> tmp_thangnd;

        base mycomplex(tmp_thangnd, 0);
        x_thangnd.push_back(mycomplex);
    }
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    fin_thangnd >> m_thangnd;
    for (int i = 0; i <= m_thangnd; i++)
    {
        int tmp_thangnd;
        fin_thangnd >> tmp_thangnd;

        base mycomplex(tmp_thangnd, 0);
        y_thangnd.push_back(mycomplex);
    }
}

void fft(vb &a_thangnd, bool revert_thangnd)
{
    int n_thangnd = (int)a_thangnd.size();

    for (int i = 1, j = 0; i < n_thangnd; ++i)
    {
        int bit = n_thangnd >> 1;
        while (j >= bit)
        {
            j = j - bit;
            bit = bit >> 1;
        }
        j = j + bit;
        if (i < j)
            swap(a_thangnd[i], a_thangnd[j]);
    }
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    for (int len = 2; len <= n_thangnd; len <<= 1)
    {
        double ang_thangnd = 2 * M_PI / len;
        if (revert_thangnd == 1)
            ang_thangnd = -ang_thangnd;
        complex<double> wlen_thangnd(cos(ang_thangnd), sin(ang_thangnd));
        for (int i = 0; i < n_thangnd; i += len)
        {
            complex<double> w(1);
            for (int j = 0; j < len / 2; ++j)
            {
                complex<double> u = a_thangnd[i + j], v = a_thangnd[i + j + len / 2] * w;
                a_thangnd[i + j] = u + v;
                a_thangnd[i + j + len / 2] = u - v;
                w = w * wlen_thangnd;
            }
        }
    }
    if (revert_thangnd == 1)
        for (int i = 0; i < n_thangnd; ++i)
            a_thangnd[i] /= n_thangnd;
}

int multiPly(int n_thangnd, int m_thangnd, vb x_thangnd, vb y_thangnd)
{
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    int p_thangnd = 1;
    while (p_thangnd < max(n_thangnd, m_thangnd))
        p_thangnd = p_thangnd << 1;
    p_thangnd = p_thangnd << 1;
    x_thangnd.resize(p_thangnd);
    y_thangnd.resize(p_thangnd);

    fft(x_thangnd, false);
    fft(y_thangnd, false);

    vector<base> h_thangnd(p_thangnd);
    for (int i = 0; i < p_thangnd; i++)
        h_thangnd[i] = x_thangnd[i] * y_thangnd[i];

    fft(h_thangnd, true);

    int res_thangnd = (int)(real(h_thangnd[0]) + 0.5);
    for (int i = 1; i <= p_thangnd; i++)
    {
        res_thangnd = res_thangnd ^ (int)(real(h_thangnd[i]) + 0.5);
    }

    return res_thangnd;
}

int main()
{
    ifstream fin_thangnd("bai211.txt");
    if (!fin_thangnd)
    {
        cerr << "Error: Unable to open file" << endl;
        return 1;
    }

    int n_thangnd, m_thangnd;
    vector<base> x_thangnd, y_thangnd;
    input(fin_thangnd, n_thangnd, m_thangnd, x_thangnd, y_thangnd);
    fin_thangnd.close();

    cout << multiPly(n_thangnd, m_thangnd, x_thangnd, y_thangnd) << endl;
    return 0;
}
/*bai 2.11 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
