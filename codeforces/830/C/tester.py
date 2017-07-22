from random import *;
from string import *;
from os import system;

MAXN = 100;
MAXM = 10**11;
MAXA = 10**9;

def create_tree(n):
    name = [i+1 for i in xrange(n)];
    E = [[name[i-1],name[randint(1,i-1)-1]] for i in xrange(2,n+1)];
    return E;

def create_test():
    f = file("in.in","w");
    n = randint(1,MAXN);
    k = randint(1,MAXM);
    f.write("%d %d\n"%(n,k));
    for i in xrange(n):
        f.write("%d "%randint(1,MAXA));
    
    f.close();
    
def run():
    system("./test > out.out");
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