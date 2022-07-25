#include <stdint.h>

using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

u64 modmult(u64 x, u64 y, u64 p)
{
    if (p < (u64(1) << 32))
        return x * y % p;

    using ld = long double;
    u64 q = ld(x) * ld(y) / ld(p);

    u64 r = x * y - p * q;
    if (r >= p) r += p;
    return r;
}
    
u64 qpow(u64 x, u64 k, u64 p)
{
    if (p == 1) return 0; // Ugh, ugly corner case
    u64 ans = 1;
    while (k)
    {
        if (k & 1) ans = modmult(ans, x, p);
        x = modmult(x, x, p);
        k >>= 1;
    }
    return ans;
}
