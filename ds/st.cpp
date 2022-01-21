#include <stdio.h>
#include <string.h>
#include <algorithm>

const int N = 1e5 + 5;
inline constexpr int log2(int n){return 31 - __builtin_clz(n);}

int a[N];

struct st
{
    int n, f[N][log2(N) + 1];

    inline void build(int *a, int n)
    {
        this -> n = n;
        for (int i = 1; i <= n; i++)
            f[i][0] = a[i];
        for (int k = 1; k <= log2(n); k++)
            for (int i = 1; i + (1 << k) <= n + 1; i++)
                f[i][k] = std::max(f[i][k - 1], f[i + (1 << (k - 1))][k - 1]);
    }

    inline int query(int l, int r)
    {
        int k = log2(r - l);
        return std::max(f[l][k], f[r - (1 << k)][k]);
    }
}
QwQ;

int main()
{
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    QwQ.build(a, n);
    
    while (q--)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        r++;
        printf("%d\n", QwQ.query(l, r));
    }
}
