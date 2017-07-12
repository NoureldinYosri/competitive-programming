import sys;
n = int(raw_input());
P = [map(int,raw_input().split()) for _ in xrange(n)];
sys.stdin = file("out.out","r");
color = map(lambda c: 1 if c == 'r' else -1, raw_input());
#print color;
X = {}
Y = {};
for p in P:
    X[p[0]] = 0;
    Y[p[1]] = 0;
for i in xrange(n):
    p = P[i];
    X[p[0]] += color[i];
    Y[p[1]] += color[i];

#print X;
#print Y;
for x in X:
    if abs(X[x]) > 1:
        print "NO";
        exit(0);
for x in Y:
    if abs(Y[x]) > 1:
        print "NO";
        exit(0);

print "YES";