n = None;
A = None;
dp = None;

def solve(s,e):
    if s == e: return 0;
    tu = tuple([s,e]);
    if tu in dp: return dp[tu];
    ret = 0;
    for m in xrange(s,e):
        ret = min(ret,solve(s,m) + solve(m + 1,e));
    ret += sum(A[s:(e+1)]);
    dp[tu] = ret;
    return ret;
 

T = int(raw_input());
for t in xrange(T):
    n = int(raw_input());
    A = map(int, raw_input().split());
    dp = {};
    print solve(0,len(A) - 1);