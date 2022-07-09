#include <stdio.h>
#include <stdint.h>

#include "utils.h"

// Primality testing for u64

bool brute_force(u64 x)
{
    for (u64 i = 2; i * i <= x; i++)
        if (x % i == 0)
            return false;
    return true;
}

bool fermat_test(u64 x, u64 b)
{
    return qpow(b, x - 1, x) == 1;
}

bool miller_rabin(u64 x, u64 b)
{
    u64 s = __builtin_ctzll(x - 1), r = x >> s; // x - 1 = r << s

    u64 c = qpow(b, r, x);
    for (int i = 0; i < s; i++)
    {
        // If c == 1, then this cannot return false:
        if (c == 1) return true;
        u64 d = modmult(c, c, x);
        if (d == 1 && c != x - 1) return false;
        c = d;
    }
    if (c != 1) return false;
    return true;
}

const u64 MR_THRESHOLD = 100000;

static const /*__attribute__((aligned(64)))*/ u64 bases[] = {
    2, 3, 61
};

bool is_prime(u64 x)
{
    if (x == 1) return false;
    if (x > MR_THRESHOLD)
    {
        for (int i = 0; i < sizeof(bases)/sizeof(u64); i++)
            if (!miller_rabin(x, bases[i]))
                return false;
        return true;
    }
    return brute_force(x);
}
