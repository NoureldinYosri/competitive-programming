from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 10;
MAXA = 5;

def create_test():
	f = file("in.in","w");
	n = 10**5;
	A = [str(randint(2,6)) for i in xrange(n)];
	f.write("%d\n"%n);
	A = " ".join(A);
	f.write("%s\n"%A);
	m = 10**5; #randint(1,MAXM);	
	f.write("%d\n "%m);
	for i in xrange(m):
		c = choice("AC");
		l = randint(1,n);
		r = randint(l+1,n+1);
		if c == 'C': r = randint(2,6);
		f.write("%c %d %d\n"%(c,l,r));
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
		break;
		run();
		if not is_correct():
			print "found";
			break;
		print "done with %d"%i;
		i += 1;

if __name__ == "__main__":
	main();
