/*bai 2.13 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <bits/stdc++.h>
#define N 101

using namespace std;

struct bigNum
{
    char sign;
    char num[N];
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

    bigNum()
    {
        sign = '1';
        for (int i = 0; i < N; i++)
            num[i] = '0';
    }

    bigNum(string &str)
    {
        int len = str.length();
        for (int i = N - 1; i >= N - len + 1; --i)
        {
            num[i] = str[len - N + i];
        }
        for (int i = 0; i <= N - len; i++)
        {
            num[i] = '0';
        }
        sign = str[0];
    }

    void multiply10(bigNum &val, int level)
    {
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
        for (int i = 0; i < N - level; i++)
        {
            val.num[i] = val.num[i + level];
        }
        for (int i = N - level; i < N; i++)
        {
            val.num[i] = '0';
        }
    }

    bigNum operator+(const bigNum &operand) const
    {
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
        bigNum result;
        int carry = 0;
        for (int i = N - 1; i >= 0; --i)
        {
            int sum = (num[i] - '0') + (operand.num[i] - '0') + carry;
            result.num[i] = sum % 10 + '0';
            carry = sum / 10;
        }
        return result;
    }

    bigNum operator-(const bigNum &operand) const
    {
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
        bigNum result;
        int borrow = 0;
        for (int i = N - 1; i >= 0; --i)
        {
            int x = num[i] - '0', y = operand.num[i] - '0';
            if (x >= y + borrow)
            {
                result.num[i] = x - (y + borrow) + '0';
                borrow = 0;
            }
            else
            {
                result.num[i] = (x + 10) - (y + borrow) + '0';
                borrow = 1;
            }
        }
        return result;
    }

    bigNum operator*(int y) const
    {
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
        bigNum result;
        result.sign = sign;
        int carry = 0;
        for (int i = N - 1; i >= 0; --i)
        {
            int x = num[i] - '0';
            int part = x * y + carry;
            result.num[i] = part % 10 + '0';
            carry = part / 10;
        }
        return result;
    }

    bigNum operator*(const bigNum &operand)
    {
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
        bigNum result;
        for (int i = N - 1; i >= 0; --i)
        {
            int x = operand.num[i] - '0';
            bigNum temp = (*this) * x;
            multiply10(temp, N - i - 1);
            result = result + temp;
        }
        result.sign = '1' - ((sign - '0') ^ (operand.sign - '0')) + '0';
        return result;
    }

    bool operator>(const bigNum &operand) const
    {
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
        for (int i = 0; i < N; i++)
        {
            if (num[i] == operand.num[i])
                continue;
            else if (num[i] > operand.num[i])
                return true;
            else
                return false;
        }
        return false;
    }
};

ostream &operator<<(ostream &stream, const bigNum &val)
{
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    stream << val.sign;
    int i = 0;
    while (i < N && val.num[i] == '0')
        i++;
    for (i; i < N; i++)
    {
        stream << val.num[i];
    }
    return stream;
}

istream &operator>>(istream &stream, bigNum &val)
{
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    string temp;
    stream >> temp;
    val = bigNum(temp);
    return stream;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    bigNum n, m;
    cin >> n;
    cin >> m;
    bigNum a = n * m, b = n * 3, c = m * 4, result;

    if (a.sign == '1')
    {
        if (b.sign == '1')
        {
            if (a > b)
            {
                result = a - b;
            }
            else
            {
                result = b - a;
                a.sign = '0';
            }
        }
        else
        {
            result = a + b;
        }
    }
    else
    {
        if (b.sign == '1')
        {
            result = a + b;
            result.sign = '0';
        }
        else
        {
            if (a > b)
            {
                result = a - b;
                result.sign = '0';
            }
            else
            {
                result = b - a;
            }
        }
    }

    /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    if (result.sign == '1')
    {
        if (c.sign == '1')
        {
            result = result + c;
        }
        else
        {
            if (result > c)
            {
                result = result - c;
            }
            else
            {
                result = c - result;
                result.sign = '0';
            }
        }
    }
    else
    {
        /*Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
        if (c.sign == '0')
        {
            result = result + c;
            result.sign = '0';
        }
        else
        {
            if (c > result)
            {
                result = c - result;
            }
            else
            {
                result = result - c;
                result.sign = '0';
            }
        }
    }

    cout <<  result;

    return 0;
}
/*bai 2.13 - tuần 11
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/