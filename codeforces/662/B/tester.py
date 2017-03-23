from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 5;
MAXA = 5;

def create_test():
	f = file("in.in","w");
	n = randint(2,MAXN);
	m = randint(1,min(MAXM,n*(n-1)/2));
	f.write("%d %d\n"%(n,m));
	E = []
	for i in xrange(n):
		for j in xrange(i):
			E.append([i+1,j+1]);
	shuffle(E);
	E = E[:m];
	for e in E:
		shuffle(e);
		f.write("%d %d %c\n"%(e[0],e[1],choice("RB")));
	f.close();
	
def run():
	system("./test < in.in > out.out");
	system("./AC < in.in > correct.out");


def is_correct():
#	system("diff out.out correct.out > err.log");
	f = file("out.out");
	F = [l for l in f];
	f.close();
	a = int(F[0]);
	f = file("correct.out");
	F = [l for l in f];
	f.close();
	b = int(F[0]);
	return a == b;

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
