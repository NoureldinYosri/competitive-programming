from random import *;
from string import *;
from os import system;
from numpy.matlib import rand

MAXN = 5;
MAXM = 5;
MAXA = 5;
MAXT = 5;

def create_test():
    f = file("input.in","w");
    for t in xrange(randint(1,MAXT)):
        N,C,D = [randint(1,MAXA) for _ in xrange(3)];
        f.write("%d %d %d\n"%(N,C,D));
        for i in xrange(N):
            d = randint(1,D);
            p = randint(2,MAXA);
            r = randint(1,p - 1);
            g = randint(1,MAXA);
            f.write("%d %d %d %d\n"%(d,p,r,g));
            
    N,C,D = [0 for _ in xrange(3)];
    f.write("%d %d %d\n"%(N,C,D));
    f.close();
    
def run():
    system("./test");
    system("python bf.py < input.in > correct.out");


def is_correct():
    system("diff output.out correct.out > err.log");
    f = file("err.log");
    F = [l for l in f];
    f.close();
    return len(F) == 0;

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