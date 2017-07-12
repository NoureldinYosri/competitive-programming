n = int(raw_input());
P = map(int, raw_input().split());
sh = best = 10**20;
for j in xrange(n):
    c = sum([abs(P[i] - i-1) for i in xrange(n)]);
    #print P,c;
    if c < best:
        best = c;
        sh = j;
    P = [P[-1]] + P[:-1];
print best,sh;