from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXX = 5;
MAXY = 5;

def create_tree(n):
    name = [i+1 for i in xrange(n)];
    E = [[name[i-1],name[randint(1,i-1)-1]] for i in xrange(2,n+1)];
    return E;

def create_test():
    f = file("in.in","w");
    S = set([tuple([randint(1,MAXX),randint(1,MAXY)]) for _ in xrange(randint(1,MAXN))]);
    f.write("%d\n"%len(S));
    for p in S:
        f.write("%d %d\n"%(p[0],p[1]));
    f.close();
    
def run():
    system("./test > out.out");
    system("python validator.py < in.in > err.log");


def is_correct():
    f = file("err.log");
    F = [l for l in f];
    f.close();
    return "YES" in F[0];

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