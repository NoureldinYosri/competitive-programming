from random import *;
from string import *;
from os import system;

MAXN = 20;
MAXM = 5;
MAXA = 5;

def create_exp(n):
    if n == 1: return 'x';
    x = randint(1,n-1);
    return choice("Mm") + create_exp(x) + create_exp(n - x);
    
def create_test():
    f = file("in.in","w");
    T = 10;
    f.write("%d\n"%T);
    for _ in xrange(T):
        s = create_exp(randint(1,MAXN));
        f.write("%s\n"%s);
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