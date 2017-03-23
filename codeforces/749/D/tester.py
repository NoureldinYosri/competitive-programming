from random import *;
from string import *;
from os import system;

MAXN = 2 * 10**5;
MAXM = 5;
MAXA = 5;
MAXK = 5;

def norm(A):
	B = [];
	for a in A:
		if len(B) == 0 or B[-1] != a: B.append(a);
	return B;

def norm2(A):
	B = []
	S = set();
	for a in A:
		if a not in S:
			B.append(a);
			S.add(a);
	return B;

def create_test():
	f = file("in.in","w");
	n = randint(1,MAXN);
	A = [randint(1,n) for i in xrange(n)];
	A = norm(A);
	f.write("%d\n"%len(A));
	for i in xrange(len(A)):
		f.write("%d %d\n"%(A[i],i + 1));
	m = randint(1,MAXM);
	f.write("%d\n"%m);
	for i in xrange(m):
		A = [randint(1,n) for k in xrange(1,MAXK)]
		A = norm2(A);
		f.write("%d"%len(A));
		for a in A:
			f.write(" %d"%a);
		f.write("\n");
	f.close();

def run():
	system("./test < in.in > out.out");
	#system("./AC < in.in > correct.out");


def is_correct():
	#system("diff out.out correct.out > err.log");
	f = file("out.out");
	F = [l for l in f];
	f.close();
	return len(F) != 0;

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
