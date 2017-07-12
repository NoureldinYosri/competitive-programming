dp = {}
def f(msk):
    if msk in dp: return dp[msk];
    r = 2**63;
    cond = True;
    for i in xrange(len(msk) - 1):
        if msk[i] == '0' and msk[i + 1] == '1':
            nmsk = msk[:i] + "110" + msk[i+2:];
            r = min(r,f(nmsk) + 1);
            cond = False;
    if cond: r = 0;
    dp[msk] = r;
    return r;

l = 10;
for i in xrange(1,l + 1):
    msk = '0'*i + '1';
    print i,f(msk)
    
