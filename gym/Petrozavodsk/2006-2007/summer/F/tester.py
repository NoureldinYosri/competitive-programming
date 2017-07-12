from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 10**6;
MAXA = 10**6;
MAXB = 10**12;
txt = ["ARRIVE","BUY"];
MX = [MAXA,MAXB];

def create_test():
    f = file("in.in","w");
    N = randint(1,MAXN);
    for i in xrange(N):
        c = choice([0,1]);
        f.write("%s %d %d\n"%(txt[c],randint(1,MAXM),randint(1,MX[c])));
    f.write("ARRIVE 5 5");
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