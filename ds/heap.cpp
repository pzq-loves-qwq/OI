#include <stdio.h>
#include <string.h>
#include <algorithm>

const int N = 1e6 + 5;

// P3378
// push(x) pushes x onto the heap
// pop() returns the min element and deletes it

struct min_heap
{
    int a[N << 1], pos;

    min_heap()
    {
        pos = 0;
        memset(a, 0x7f, sizeof a);
    }

    void push(int i)
    {
        a[++pos] = i;
        up(pos);
    }

    int pop()
    {
        int ans = a[1];
        a[1] = a[pos];
        pos--;
        down(1);
        return ans;
    }

private:

    inline int lson(int i)
    {
        return i << 1;
    }

    inline int rson(int i)
    {
        return (i << 1) | 1;
    }

    bool ok(int i)
    {
        bool left = (lson(i) >= pos) || a[i] <= a[lson(i)];
        bool right = (rson(i) >= pos) || a[i] <= a[rson(i)];
        return left && right;
    }

    void down(int i)
    {
        int son;
        while (lson(i) <= pos)
        {
            if (a[lson(i)] < a[rson(i)])
                son = lson(i);
            else
                son = rson(i);
            #ifndef ONLINE_JUDGE
            printf("down(): son = %d\n", son);
            #endif
            if (a[son] < a[i])
            {
                std::swap(a[i], a[son]);
                i = son;
            }
            else
                break;
        }
    }

    void up(int i)
    {
        while (i != 1 && a[i] < a[i >> 1])
        {
            std::swap(a[i], a[i >> 1]);
            i >>= 1;
        }
    }
} qwq;

int main()
{
    int op, x, n;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d", &x);
            qwq.push(x);
        }
        else if (op == 2)
        {
            printf("%d\n", qwq.a[1]);
        }
        else if (op == 3)
        {
        	int ans = qwq.pop();
		}
		#ifndef ONLINE_JUDGE
		printf("debug: qwq = ");
        for (int i = 1; i <= qwq.pos; i++)
        {
            printf("%d ", qwq.a[i]);
        }
        printf("\n");
        #endif
    }
}
