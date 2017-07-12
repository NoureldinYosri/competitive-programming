from random import randint;
from os import system;

def solve(n,A,B):
	for msk in xrange(1 << n):
		sa = sb = 0;
		for i in xrange(n):
			if msk & (1 << i):
				sa += A[i];
				sb += B[i];
		if 2*sa > sum(A) and 2*sb > sum(B): return 1;
	return 0;

def create_case():
	n = randint(1,20);
	A = [randint(1,100000) for i in xrange(n)];
	B = [randint(1,100000) for i in xrange(n)];
	if solve(n,A,B): return n,A,B;
	return create_case();	
	

def gen():
	f = file("input.in","w");
	n,A,B = create_case();
	f.write("%d\n"%n);
	f.write(" ".join(map(str,A)));
	f.write("\n");
	f.write(" ".join(map(str,B)));
	f.write("\n");
	f.close();

t = 1;
while True:
	gen();
	system("./test < input.in > output.out");
	f = file("output.out","r");
	F = [l for l in f];
	if not len(F): 
		print "found"
		break;
	print "done with ",t;
	t += 1;
