from random import *;
from os import *;

MAXN = 3;
MAXM = 3;
MAXA = 7;

def create_test():
	f = file("in.in","w");
	n = randint(1,MAXN);
	m = randint(1,MAXM);
	f.write("%d %d\n"%(n,m));
	for i in xrange(m):
		l = randint(1,n);
		r = randint(l,n);
		v = randint(0,MAXA);
		f.write("%d %d %d\n"%(l,r,v));
	f.close();

def run():
	system("./test < in.in > out.out");
	system("./AC < in.in > AC.out");	

def is_correct():
	system("diff out.out AC.out > err.log");
	F = file("err.log","r");
	F = [l for l in F];
	return len(F) == 0;

def main():
	t = 1;
	while True:
		create_test();
		run();
		if not is_correct():
			print "found";
			break;
		print "done with %d"%t;
		t += 1;

if __name__ == "__main__":
	main();
