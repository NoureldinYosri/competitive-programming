from random import *;
from string import *;
from os import system;

MAXN = 10**6;
MAXM = 10**15;
MAXA = 5;

def create_test():
    f = file("input.in","w");
    T = randint(1,MAXA);
    f.write("%d\n"%T);
    for t in xrange(T):
        f.write("%d %d\n"%(randint(1,MAXN),randint(1,MAXM)));
    f.close();
    
def run():
    system("./test ");
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