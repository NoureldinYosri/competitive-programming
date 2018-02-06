import sys;

def solve(a,m,b):
    if b >= m: return -1;
    vis = [0 for i in xrange(m)];
    p = 1%m;
    i = 0;
    while p != b and not vis[p]:
        vis[p] = 1;
        p = (p * a)%m;
        i += 1;
    if p != b: return -1;
    return i;

for l in sys.stdin:
    if "0 0 0" in l: break;
    a,m,b = map(int, l.split());
    res = solve(a,m,b);
    if res == -1: print "No Solution"
    else: print res;