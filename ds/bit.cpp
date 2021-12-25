#include <stdio.h>
#include <string.h>
#include <algorithm>

// P3374
// modify(i, k) adds k to position i
// query(i) queries the sum of [1, i]

typedef long long ll;
const int N = 5e5 + 5;

inline int lowbit(int n)
{
    return n & -n;
}

struct BIT
{
    int n;
    ll tree[N];

    inline BIT() {}
    inline BIT(int nn) {n = nn; }

    inline void modify(int i, ll k)
    {
        for (; i <= n; i += lowbit(i))
            tree[i] += k;
    }

    inline ll query(int i)
    {
        ll ans = 0;
        for (; i; i -= lowbit(i))
            ans += tree[i];
        return ans;
    }
}
QwQ;

int main()
{
    int n, q;
    scanf("%d %d", &n, &q);
    QwQ.n = n;
    for (int i = 1; i <= n; i++)
    {
        int k;
        scanf("%d", &k);
        QwQ.modify(i, k);
    }
    
    while (q--)
    {
        int op, x, y;
        scanf("%d %d %d", &op, &x, &y);
        if (op == 1)
            QwQ.modify(x, y);
        else
            printf("%d\n", QwQ.query(y) - QwQ.query(x - 1));
    }
    return 0;
}
