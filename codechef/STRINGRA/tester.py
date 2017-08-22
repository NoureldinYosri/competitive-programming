from random import *;
import checker;
import os;

MAXN = 10;
MAXM = 1000;

A = None;

def create(mustHaveSol = False):
    n = None;
    E = None;
    m = None;
    global A;
    if mustHaveSol:
        n = randint(1,MAXN);
        A = [randint(1,5) for i in xrange(n)];
        E = checker.create(A);      
        m = len(E);  
    else:
        n = randint(1,MAXN);
        E = [];
        for i in xrange(n):
            cnt = randint(0,MAXM);
            while cnt:
                j = randint(i+1,n);
                E.append([i,j]);
                cnt -= 1;
        S = set();
        for e in E:
            S.add(tuple(e));
        E = list(S);
        m = len(E);
    f = file("in.in","w");
    f.write("1\n%d %d\n"%(n,m));
    for e in E:
        f.write("%d %d\n"%(e[0],e[1]));
    f.close();


if __name__ == "__main__":
    T = 0;
    while True:
        mustHaveSol = choice([True,False]);
        create(mustHaveSol);
        os.system("./test < in.in > out.out");
        verdict = checker.validate("in.in","out.out");
        if verdict == False:
            print "found";
            break;
        elif verdict != True and mustHaveSol:
            print "found";
            print A;
            break; 
        T += 1;
        print "done with ",T;