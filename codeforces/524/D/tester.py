from random import *;
from string import *;
from os import system;

MAXN = 200;
MAXM = 5;
MAXA = 5;
MAXT = 200;

def create_test():
	f = file("in.in","w");
	n = randint(1,MAXN);
	M = randint(1,MAXM);
	T = randint(1,MAXT);
	f.write("%d %d %d\n"%(n,M,T));
	l = 0;
	for i in xrange(n):
		l = t = randint(l,24*3600 - T - 1);
		h = t/3600; t %= 3600;
		m = t/60;
		s = t%60;
		f.write("%d:%d:%d\n"%(h,m,s));
	f.close();

def run():
	system("./test < in.in > out.out");
	system("./AC < in.in > correct.out");


def is_correct():
	f = file("out.out","r");
	F = [l for l in f];
	x = F[0];
	f.close();
	f = file("correct.out","r");
	F = [l for l in f];
	y = F[0];
	f.close();
	return x == y;

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
