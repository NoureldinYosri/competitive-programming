from random import *;
from string import *;
from os import system;

MAXN = 6;
MAXM = 5;
MAXA = 5;

def create_test():
	f = file("in.in","w");	
	n,m = randint(2,MAXN),randint(1,MAXM);
	name = [i+1 for i in xrange(n)];
	shuffle(name);
	f.write("%d %d\n"%(n,m));
	for i in xrange(2,n + 1):
		f.write("%d %d\n"%(name[i - 1],name[randint(1,i-1)-1]));
	q = randint(1,min(n-1,m));
	Q = [[1,i+2] for i in xrange(n-1)];
	shuffle(Q);
	Q = Q[:q];
	Q = Q + [[2,randint(1,n)] for i in xrange(m - q)];
	shuffle(Q);
	for q in Q:
		f.write("%d %d\n"%(q[0],q[1]));
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
