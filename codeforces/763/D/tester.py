from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 5;
MAXA = 5;
P = [2,3,5,7,11];

def create_test():
	f = file("in.in","w");
	m = choice(P);
	a = randint(0,m-1);
	d = randint(1,m-1);
	vis = [0 for i in xrange(m)];
	A = []
	while not vis[a]:
		vis[a] = 1;
		A.append(a);
		a = (a + d)%m;
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
