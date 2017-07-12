from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 5;
MAXA = 5;

def get(root,cnt,G):
    A = [];
    q = [root];
    vis = set(); vis.add(root);
    for i in xrange(cnt):
        u = choice(q);
        A.append(u);
        q.remove(u);
        for v in G[u]:
            if v not in vis:
                vis.add(v);
                q.append(v);
    return A;

def create_test():
    f = file("in.in","w");
    n = randint(1,MAXN);
    m = randint(1,MAXM);
    f.write("%d %d\n"%(n,m));
    E = [[i,randint(1,i-1)] for i in xrange(2,n+1)];
    G = [[] for i in xrange(n+1)];
    for e in E:
        G[e[0]].append(e[1]);
        G[e[1]].append(e[0]);
    F = [get(randint(1,n),randint(0,n),G) for i in xrange(m)];
    R = [[] for i in xrange(n+1)];
    for i in xrange(m):
        for x in F[i]:
            R[x].append(i+1);
    for i in xrange(1,n+1):
        f.write("%d "%len(R[i]));
        for x in R[i]:
            f.write("%d "%x);
        f.write("\n");
    for e in E:
        f.write("%d %d\n"%(e[0],e[1]));
        
def run():
    system("./test > out.out");
    system("./AC < in.in > correct.out");


def read(s):
    f = file(s,"r");
    L = [l for l in f];
    x = int(L[0]);
    f.close();
    return x;

def is_correct():
    x = read("out.out");
    y = read("correct.out");
    return x == y;

def main():
    i = 1;
    while True:
        create_test();
        run();
        if not is_correct():
            print "found";
            break;
        print "done with %d"%i;
        i += 1;

if __name__ == "__main__":
    main();