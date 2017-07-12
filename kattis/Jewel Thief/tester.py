from random import *;
from string import *;
from os import system;

MAXN = 2*10**1;
MAXM = 2*10**1;
MAXW = 2*10**1;
MAXV = 10;
MAXX = 3;
def create_test():
    f = file("in.in","w");
    n = randint(1,MAXN);
    X = [];
    m = 0;
    for i in xrange(1,MAXX + 1):
        y = randint(3,5);
        for j in xrange(y):
            m += 1;
            X.append([i,randint(1,MAXV)]);
    f.write("%d %d\n"%(m,n));
    for p in X:
        f.write(" ".join(map(str, p)));
        f.write("\n");
    f.close();
def run():
    system("./test > out.out 2> err.log");
    system("java thief_font < in.in > correct.out");


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