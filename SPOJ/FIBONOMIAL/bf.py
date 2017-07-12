mod = 10**9 + 7;
def solve(n,x):
    if n == 1: return x % mod; 
    x %= mod;
    u = v = 1;
    s = (x + x**2)%mod;
    px = x**2;
    i = 2;
    while i < n:
        px = (px * x)%mod;
        u,v = v,(u + v)%mod;
        s += v*px;
        s %= mod;
        i += 1;
    return s;

for _ in xrange(int(raw_input())):
    n,x = map(int,raw_input().split());
    print solve(n,x);