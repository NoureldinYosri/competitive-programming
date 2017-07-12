def gcd(a,b):
    while b:a,b = b,a%b;
    return a;

def f(a,b):
    ret = 0;
    freq = {};
    for i in xrange(a,b+1):
        ret += i*b/gcd(i,b);
        x = i*b/gcd(i,b);
        if x not in freq: freq[x] = 0;
        freq[x] += 1;
    return ret,freq;

T = int(raw_input());
for t in xrange(T):
    a,b = map(int ,raw_input().split());
    ans,_ = f(a,b);
    print ans%(10**9 + 7);