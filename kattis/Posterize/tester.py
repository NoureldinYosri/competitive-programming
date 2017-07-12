from random import *;
from string import *;
from os import system;

MAXN = 256;
MAXM = 256;
MAXA = 2**26;

def create_test():
    f = file("in.in","w");
    d = randint(1,MAXN);
    K = randint(1,MAXM);
    I = sample(range(0,256),d);
    I.sort();
    f.write("%d %d\n"%(d,K));
    for r in I:
        f.write("%d %d\n"%(r,randint(1,MAXA)));
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