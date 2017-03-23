from random import *;
from string import *;
from os import system;

MAXN = 1000;
MAXM = 1000;
MAXA = 1000;
MAXQ = 1000;

def create_test():
	f = file("grass.in","w");
	N = randint(2,MAXN);
	M = randint(1,MAXM); M = min(M,N*(N - 1)/2);
	K = randint(1,N);
	Q = randint(1,MAXQ);
	f.write("%d %d %d %d\n"%(N,M,K,Q));
	E = [];
	for i in xrange(N):
		for j in xrange(i):
			E.append([i,j]);
	shuffle(E);
	E = E[:M];
	for e in E:
		f.write("%d %d %d\n"%(e[0],e[1],randint(1,MAXA)));
	for i in xrange(N):
		f.write("%d "%randint(1,K));
	f.write("\n");
	for i in xrange(Q):
		f.write("%d %d\n"%(randint(1,N),randint(1,K)));
	f.close();

		
def run():
	system("./test");
	system("./AC < grass.in > correct.out");


def is_correct():
	system("diff grass.out correct.out > err.log");
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
