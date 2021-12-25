#include <stdio.h>
#include <string.h>
#include <algorithm>

// P3367
// fa(i) queries the set i is in
// merge(i, j) merges the set i, j
// init(n) initializes the dsu

const int N = 1e4 + 5;
int father[N], size[N];

inline int fa(int u)
{
    if (u == father[u])
        return u;
    return father[u] = fa(father[u]);
}

inline void merge(int a, int b)
{
    a = fa(a), b = fa(b);
    if (size[a] < size[b])
        std::swap(a, b);
    father[b] = a;
    size[a] += size[b];
    return;
}

inline void init(int n)
{
    for (int i = 1; i <= n; i++)
        father[i] = i, size[i] = 1;
}

int main()
{
    int n, q;
    scanf("%d %d", &n, &q);
    init(n);

    while (q--)
    {
        int op, x, y;
        scanf("%d %d %d", &op, &x, &y);
        if (op == 1)
            merge(x, y);
        if (op == 2)
        {
            if (fa(x) == fa(y))
                printf("Y\n");
            else
                printf("N\n");
        }
    }
    return 0;
}
