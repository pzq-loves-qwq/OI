#include <stdio.h>
#include <string.h>
#include <algorithm>

const int SIZE = 100;
struct bigint
{
    int a[SIZE];

    bigint()
    {
        memset(a, 0, sizeof a);
    }

    bigint(int x)
    {
        memset(a, 0, sizeof a);
        int p = 0;
        while (x)
        {
            a[p++] = x % 10;
            x /= 10;
        }
    }
};

bigint operator+(const bigint &x, const bigint &y)
{
    bigint ans = 0;
    int carry = 0;
    for (int i = 0; i < SIZE; i++)
    {
        ans.a[i] = (x.a[i] + y.a[i] + carry) % 10;
        carry = (x.a[i] + y.a[i] + carry) / 10;
    }
    return ans;
}

bigint operator*(const bigint &x, const bigint& y)
{
    bigint ans = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; i + j < SIZE; j++)
            ans.a[i + j] += x.a[i] * y.a[j];
    for (int i = 0; i < SIZE - 1; i++)
    {
        ans.a[i + 1] += ans.a[i] / 10;
        ans.a[i] %= 10;
    }
    return ans;
}

bool operator<=(const bigint &x, const bigint &y)
{
    for (int i = SIZE - 1; i >= 0; i--)
    {
        if (x.a[i] < y.a[i])
            return true;
        else if (x.a[i] > y.a[i])
            return false;
    }
    return false;
}

bigint in()
{
    bigint a = 0;
    int p = 0;
    char c = '\0';
    while (scanf("%c", &c))
    {
        if ('0' <= c && c <= '9')
            a.a[p++] = c - '0';
        else
            break;
    }
    std::reverse(a.a, a.a + p);
    return a;
}

void out(const bigint& a)
{
    bool started = false;
    for (int i = SIZE - 1; i >= 0; i--)
    {
        started |= a.a[i] != 0;
        if (started)
            printf("%d", a.a[i]);
    }
    if (!started)
        printf("0");
}
