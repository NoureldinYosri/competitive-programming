from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 5;
MAXA = 10;

def create_test():
	f = file("in.in","w");
	T = randint(1,2);
	f.write("%d\n"%T);
	for t in xrange(T):
		n = randint(1,MAXN);
		f.write("%d\n"%n);
		P = [randint(1,i-1) if i > 1 else 0 for i in xrange(n+1)];
		#name = [i+1 for i in xrange(n)];
		#shuffle(name);
		#name = [0] + name;
		for i in xrange(1,n+1):
			f.write("%d "%P[i]);
			f.write("%d\n"%randint(0,MAXA));
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
