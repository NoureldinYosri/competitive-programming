from random import *;
from string import *;
from os import system;
from numpy.matlib import rand
import time
MAXN = 100000;
MAXM = 5;
MAXA = 5;

def create_test():
    f = file("in.in","w");
    n = 40; #randint(1,MAXN);
    k = 100;
    f.write("%d %d\n"%(n,k));
    for i in xrange(2,n+1):
        l = 1; #randint(1,10**5);
        r = 10**5; #randint(l,10**5);
        f.write("%d %d %d %d\n"%(i,min(i-1,randint(1,20)),l,r));
    f.close();
    
def run():
    system("./test");
    #system("./AC < in.in > correct.out");


def is_correct():
    return 1;
    system("diff out.out correct.out > err.log");
    f = file("err.log");
    F = [l for l in f];
    f.close();
    return len(F) == 0;

def main():
    i = 1;
    t = 0;
    while i <= 100:
        create_test();
        st = time.time();
        run();
        t += time.time() - st;
        if not is_correct():
            print "found";
            break;
        print "done with %d"%i;
        i += 1;
    print "average = ",t/1000.0;
if __name__ == "__main__":
    main();