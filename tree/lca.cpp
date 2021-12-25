#include <stdio.h>
#include <string.h>
#include <algorithm>

inline constexpr int log2(int n) {return 31 - __builtin_clz(n);}

const int N = 5e5 + 5;

struct edge
{
    int u, v, next;
}
e[N << 1]; int cnt, head[N];

inline void add_edge(int u, int v)
{
    e[cnt].u = u, e[cnt].v = v, e[cnt].next = head[u];
    head[u] = cnt++;
}

int depth[N], top[N][log2(N)];

inline void dfs(int u, int f)
{
    depth[u] = depth[f] + 1;
    top[u][0] = f;

    for (int i = 1; i <= log2(depth[u]); i++)
        top[u][i] = top[top[u][i - 1]][i - 1];

    for (int i = head[u]; ~i; i = e[i].next)
        if (e[i].v != f)
        {
            int v = e[i].v;
            dfs(v, u);
        }
}

inline int lca(int u, int v)
{
    if (depth[u] < depth[v])
        std::swap(u, v);
    while (depth[u] > depth[v])
        u = top[u][log2(depth[u] - depth[v])];
    if (u == v)
        return u;
    for (int i = log2(depth[u]); i >= 0; i--)
        if (top[u][i] != top[v][i])
            u = top[u][i], v = top[v][i];
    return top[u][0];
}

int main()
{
    memset(head, -1, sizeof head);

    int n, q, rt;
    scanf("%d %d %d", &n, &q, &rt);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v), add_edge(v, u);
    }

    dfs(rt, 0);

    while (q--)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        printf("%d\n", lca(u, v));
    }
    return 0;
}
