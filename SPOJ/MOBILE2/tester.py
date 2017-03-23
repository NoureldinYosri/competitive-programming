from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 5;
MAXA = 5;

def create_test():
	f = file("in.in","w");
	T = 2;
	f.write("%d\n"%T);
	for t in xrange(T):
		n = randint(1,MAXN);
		f.write("%d\n"%n);
		S = set([1]);
		P = [0 for i in xrange(n + 1)];
		L = [-1 for i in xrange(n + 1)];
		R = [-1 for i in xrange(n + 1)];
		for i in xrange(2,n + 1):
			P[i] = choice(list(S));
			S.add(i);
			if L[P[i]] != -1:
				R[P[i]] = i;
				S.remove(P[i]);
			else:
				L[P[i]] = i;
		for i in xrange(1,n+1):
			f.write("%d %d\n"%(L[i],R[i]));
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
