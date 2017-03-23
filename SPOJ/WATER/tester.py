from random import *;
from string import *;
from os import system;

MAXN = 7;
MAXM = 7;
MAXA = 100;
MAXT = 5;

def create_test():
	f = file("in.in","w");
	T = randint(1,MAXT);
	f.write("%d\n"%T);
	for t in xrange(T):
		m = randint(1,MAXM);
		n = randint(1,MAXN);
		f.write("%d %d\n"%(m,n));
		for i in xrange(m):
			R = [str(randint(1,MAXA)) for _ in xrange(n)];
			R = " ".join(R);
			f.write("%s\n"%R);
	f.close();

def run():
	system("java main < in.in > out.out");
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
