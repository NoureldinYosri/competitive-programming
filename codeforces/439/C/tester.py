from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 5;
MAXA = 5;

def create_test():
	f = file("in.in","w");
	n = randint(1,MAXN);
	k = randint(1,n);
	p = randint(0,k-1);
	f.write("%d %d %d\n"%(n,k,p));
	A = [i+1 for i in xrange(MAXA)];
	shuffle(A);
	for i in xrange(n):
		f.write("%d "%A[i]);
	f.close();

def run():
	system("./test < in.in > out.out");
	system("./AC < in.in > correct.out");


def read(name):
	f = file(name);
	L = [l for l in f];
	f.close();
	return L[0];

def is_correct():
	return read("out.out") == read("correct.out");

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
