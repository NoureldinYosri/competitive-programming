from random import *
from os import *;

MAXN = 5*10**5;
MAXM = 5*10**5;

def create_test():
	F = file("in.in","w");
	n = randint(1,MAXN);
	F.write("%d\n"%n);
	for i in xrange(n - 1):
		v = randint(1,i + 1);
		F.write("%d %d\n"%(v,i + 2));
	m = randint(1,MAXM);
	F.write("%d\n"%m);
	for i in xrange(m):
		F.write("%d %d\n"%(randint(1,3),randint(1,n)));
	F.close();

def run():
	system("./AC < in.in > AC.out");
	system("./test < in.in > out.out");

def is_correct():
	system("diff AC.out out.out > err.log");
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
