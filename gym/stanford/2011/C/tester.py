from random import *;
from string import *;
from os import system;

MAXN = 10;
MAXM = 10;
MAXA = 10;

def create_test():
	f = file("in.in","w");
	n = 100000;
	f.write("%d\n"%n);
	for i in xrange(1,n):
		f.write("%d %d %d\n"%(0,i,1000));
	u = randint(0,n-1);
	v = randint(0,n-1);
	f.write("%d %d %d\n"%(u,v,randint(1,MAXA)));
	m = randint(1,MAXM);
	f.write("%d\n"%m);
	for i in xrange(m):	
		f.write("%d %d\n"%(randint(0,n-1),randint(0,n-1)));
	f.write("0\n");
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
