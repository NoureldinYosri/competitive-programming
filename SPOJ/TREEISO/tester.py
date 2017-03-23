from random import *;
from string import *;
from os import system;

MAXN = 10**5;
MAXM = 5;
MAXA = 5;

def create_test():
	f = file("in.in","w");
	T = 1;
	f.write("%d\n"%T);
	for t in xrange(T):
		n = randint(1,MAXN);
		f.write("%d\n"%n);
		for i in xrange(2,n + 1):	
			f.write("%d %d\n"%(i,randint(1,i-1)));
		for i in xrange(2,n + 1):	
			f.write("%d %d\n"%(i,randint(1,i-1)));
	f.close();

def run():
	f = file("out.out","w");
	f.close();
	system("./test < in.in > out.out");
	#system("./AC < in.in > correct.out");


def is_correct():
#	system("diff out.out correct.out > err.log");
	f = file("out.out");
	F = [l for l in f];
	f.close();
	return len(F) != 0;

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
