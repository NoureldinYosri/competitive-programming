from __builtin__ import raw_input
N = C = D = None;
day = buying_price = selling_price = revenue = dp = None;

def solve(n):
    if n == 0: return C;
    if n in dp: return dp[n];
    ret = -(1 << 60);
    for i in xrange(n):
        if day[n] == day[i]: continue;
        cur = solve(i) + (day[n] - day[i] - 1)*revenue[i] + selling_price[i];
        if cur >= buying_price[n]:
            ret = max(ret,cur - buying_price[n]);
    dp[n] = ret;
#    print n,day[n],ret;
    return ret;

t = 1;
while True:
    N,C,D = map(int, raw_input().split());
    if N == 0 and C == 0 and D == 0: break;
    day = [0 for _ in xrange(N + 2)];
    buying_price = [0 for _ in xrange(N + 2)];
    selling_price = [0 for _ in xrange(N + 2)];
    revenue = [0 for _ in xrange(N + 2)];
    dp = {};
    I = [];
    for i in xrange(1,N + 1):
        I.append(map(int, raw_input().split()));
    I.sort();
    for i in xrange(1,N + 1):
        day[i],buying_price[i],selling_price[i],revenue[i] = I[i - 1];
    day[N + 1] = D + 1;
    print "Case %d: %d"%(t,solve(N+1));
    t += 1;