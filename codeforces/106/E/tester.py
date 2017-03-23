from random import *;
from string import *;
from os import system;

MAXN = 10**5;
MAXM = 100;
MAXA = 10**3;

def create_test():
	f = file("in.in","w");
	L = randint(1,MAXN);
	S = "".join([choice(uppercase[:2]) for i in xrange(L)]);
	m = randint(1,MAXM);
	f.write("%s\n%d\n"%(S,m));
	for i in xrange(m):	
		L = randint(1,MAXA);
		S = "".join([choice(uppercase[:2]) for i in xrange(L)]);
		f.write("%s\n"%S);
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
