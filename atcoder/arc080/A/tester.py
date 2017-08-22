from random import *;
from string import *;
from os import system;

MAXN = 8;
MAXM = 5;
MAXA = 5;

def create_tree(n):
	name = [i+1 for i in xrange(n)];
	E = [[name[i-1],name[randint(1,i-1)-1]] for i in xrange(2,n+1)];
	return E;

def create_test():
	f = file("in.in","w");
	n = randint(1,MAXN);
	f.write("%d\n"%n);
	A = [randint(0,3) for i in xrange(n)];
	f.write(" ".join(map(str,A)));
	f.close();

def run():
	system("./test > out.out");
	system("python bf.py < in.in > correct.out");


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
