from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 5;
MAXA = 5;
MAXL = 5;

def create_tree(n):
    name = [i+1 for i in xrange(n)];
    E = [[name[i-1],name[randint(1,i-1)-1]] for i in xrange(2,n+1)];
    return E;

def create_test():
    f = file("in.in","w");
    n = 2*10**5;
    m = n;
    f.write("%d %d\n"%(n,m));
    LEN = 2*10**5;
    for i in xrange(n):
        l = randint(1,LEN - (n-1-i));
        if i == n-1: l = LEN;
        LEN -= l;
        f.write("".join([choice(lowercase) for _ in xrange(l)]));
        f.write("\n");
    for i in xrange(m):
        l = randint(1,n);
        r = randint(l,n);
        k = randint(1,n);
        f.write("%d %d %d\n"%(l,r,k));
    f.close();

import time;
def run():
    t1 = time.time();
    system("./test > out.out");
    t2 = time.time();
    system("./AC < in.in > correct.out");
    t3 = time.time();
    return (t2 - t1 + 0.0)/(t3 - t2);

def is_correct():
    system("diff out.out correct.out > err.log");
    f = file("err.log");
    F = [l for l in f];
    f.close();
    return len(F) == 0;

def main():
    i = 1;
    cnt = 50
    r = 0;
    while i <= cnt:
        create_test();
        print "running";
        t = run();
        r += t;
        print t;
        if not is_correct():
            print "found";
            break;
        print "done with %d"%i;
        i += 1;
    print r/cnt * 100;
if __name__ == "__main__":
    main();