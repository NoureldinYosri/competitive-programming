from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 5;
MAXA = 5;
P = [2,3,5,7,11,13,17,19,23,29,31];
P = [ 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89];
D = None;

def create_test():
	global D;
	f = file("in.in","w");
	m = choice(P);
	a = randint(0,m-1);
	d = randint(m/2,m-1);
	D = d;
	vis = [0 for i in xrange(m)];
	A = []
	n = randint(1,m/2);
	while not vis[a]:
		vis[a] = 1;
		A.append(a);
		a = (a + d)%m;
		n -= 1;
		if not n: break;
	shuffle(A);
	f.write("%d %d\n"%(m,len(A)));
	A = [str(a) for a in A];
	S = " ".join(A);
	f.write("%s\n"%S);
	f.close();

def run():
	system("./test < in.in > out.out");
	return;
	system("./AC < in.in > correct.out");


def is_correct():
	#system("diff out.out correct.out > err.log");
	f = file("out.out");
	F = [l for l in f];
	f.close();
	return F[0] != "-1";

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
