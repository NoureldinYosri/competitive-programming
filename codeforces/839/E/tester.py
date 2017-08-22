from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 5;
MAXA = 5;

def create_tree(n):
	name = [i+1 for i in xrange(n)];
	E = [[name[i-1],name[randint(1,i-1)-1]] for i in xrange(2,n+1)];
	return E;

def create_test():
	f = file("in.in","w");
	n = randint(2,10);
	k = randint(1,10);
	f.write("%d %d\n"%(n,k));
	G = [[0 for i in xrange(n)] for j in xrange(n)];
	for i in xrange(n):
		for j in xrange(i):
			G[i][j] = G[j][i] = randint(0,1);
	for i in xrange(n):
		f.write(" ".join(map(str,G[i])));
		f.write("\n");
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
