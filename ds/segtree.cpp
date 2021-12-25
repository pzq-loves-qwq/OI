#include <stdio.h>
#include <string.h>
#include <algorithm>

// P3372
// build(a, i, l, r) initializes node i with a[] with interval [l, r)
// query(i, l, r) queries the sum [l, r) on node i
// modify(i, l, r, k) adds k to [l, r) on node i

typedef long long ll;
const int N = 1e5 + 5;

struct node
{
    int l, r;
    ll sum, lazy;
};
struct segtree
{
    node a[N << 2];

    #define u a[i]
    #define lc a[i << 1]
    #define rc a[i << 1 | 1]
    #define len(v) (v.r - v.l)
    #define mid (u.l + u.r) >> 1
    
    inline void pushup(int i)
    {
        u.sum = lc.sum + rc.sum;
    }

    inline void pushdown(int i)
    {
        if (u.lazy == 0)
            return;
        lc.sum  += u.lazy * len(lc);
        lc.lazy += u.lazy;
        rc.sum  += u.lazy * len(rc);
        rc.lazy += u.lazy;
        u.lazy = 0;
    }

    inline void build(ll *init, int i, int l, int r)
    {
        u.l = l, u.r = r, u.lazy = 0;
        if (len(u) == 1)
        {
            u.sum = init[l];
            return;
        }
        build(init, i << 1, l, mid);
        build(init, i << 1 | 1, mid, r);
        pushup(i);
    }

    inline ll query(int i, int l, int r)
    {
        if (r <= u.l || l >= u.r)
            return 0;
        if (l <= u.l && r >= u.r)
            return u.sum;
        pushdown(i);
        return query(i << 1, l, r) + query(i << 1 | 1, l, r);
    }

    inline void modify(int i, int l, int r, ll k)
    {
        if (r <= u.l || l >= u.r)
            return;
        if (l <= u.l && r >= u.r)
        {
            u.sum  += k * len(u);
            u.lazy += k;
            return;
        }
        pushdown(i);
        modify(i << 1, l, r, k), modify(i << 1 | 1, l, r, k);
        pushup(i);
    }

    #undef u
    #undef lc
    #undef rc
    #undef len
    #undef mid
}
QwQ;

ll init[N];

int main()
{
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &init[i]);
    QwQ.build(init, 1, 1, n + 1);

    while (q--)
    {
        int op, x, y; ll k;
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d %d %lld", &x, &y, &k);
            QwQ.modify(1, x, y + 1, k);
        }
        if (op == 2)
        {
            scanf("%d %d", &x, &y);
            printf("%lld\n", QwQ.query(1, x, y + 1));
        }
    }
    return 0;
}
