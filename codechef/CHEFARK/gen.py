from random import randint;
from os import system;

n = k = A = None;
corr = None;
S = None;
MAX = 5;

def create_test():
	global n,k,A;	
	f = file("in.in","w");
	n = randint(1,MAX);
	k = randint(1,MAX);
	A = [randint(-MAX,MAX) for i in xrange(n)];
	f.write("1\n%d %d\n"%(n,k));
	f.write(" ".join([str(x) for x in A]));
	f.close();

def solve():
	global S;	
	S = set();
	def solve2(i,m):
		if m == 0:
			S.add(" ".join([str(x) for x in A]));
			return;
		if i == n: return;		
		for j in xrange(0,m + 1,2) : solve2(i + 1,j);
		A[i] = -A[i];
		for j in xrange(1,m + 1,2) : solve2(i + 1,j);
		A[i] = -A[i];

	solve2(0,k);
	return len(S);

def run():
	system("./test < in.in > out.out");

def is_correct():
	global corr
	f = file("out.out","r");
	f = [l for l in f];
	f = int(f[0]);
	corr = solve();
	print f,corr;
	return f == corr;

t = 1;
while True:
	create_test();
	run();
	if not is_correct():
		print "found ,correct = %d"%corr;
		for a in S: print a;		
		break;
	print "done with %d"%t;
	t += 1;
