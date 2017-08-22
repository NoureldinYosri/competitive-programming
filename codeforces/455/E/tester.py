from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 5;
MAXA = 5;

def create_tree(n):
    name = [i+1 for i in xrange(n)];
    E = [[name[i-1],name[randint(1,i-1)-1]] for i in xrange(2,n+1)];
    return E;

def create_test():
    f = file("in.in","w");
    n = MAXN;#randint(1,MAXN);
    f.write("%d\n"%n);
    A = [randint(1,MAXA) for i in xrange(n)];
    f.write(" ".join(map(str,A)));
    f.write("\n");
    m = randint(1,MAXM);
    f.write("%d\n"%m)
    for _ in xrange(m):
        j = randint(1,n);
        i = randint(1,j);
        f.write("%d %d\n"%(i,j));
    f.close();
    
def run():
    system("./test < in.in > out.out");
    system("./AC < in.in > correct.out");


def is_correct():
    system("diff out.out correct.out > err.log");
    f = file("err.log");
    F = [l for l in f];
    f.close();
    return len(F) == 0;

def main():
    #system("g++ AC.cpp -std=c++11 -o AC");
    system("g++ main.cpp -std=c++11 -o test");
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