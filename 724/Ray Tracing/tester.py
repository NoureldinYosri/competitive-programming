from random import *;
from string import *;
from os import system;

MAXN = 10**5;
MAXM = 10**5;
MAXK = 10**5;


def generate(n,m):
    return tuple([randint(1,n-1),randint(1,m-1)]);
def create_test():
    f = file("in.in","w");
    n = randint(2,MAXN);
    m = randint(2,MAXM);
    k = randint(1,MAXK);
    A = [generate(n,m) for _ in xrange(k)];
    A = set(A);
    k = len(A);
    f.write("%d %d %d\n"%(n,m,k));
    for p in A:
        V = list(p);
        f.write("%d %d\n"%(V[0],V[1]));
    f.close();
    
def run():
    system("./test ");
    system("./AC < in.in > correct.out");


def is_correct():
    system("diff out.out correct.out > err.log");
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