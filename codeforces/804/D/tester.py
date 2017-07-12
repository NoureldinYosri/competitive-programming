from random import *;
from string import *;
from os import system;

MAXN = 10;
MAXA = 5;

def create_test():
	f = file("in.in","w");
	n = randint(1,MAXN);
	E = [[i,randint(1,i-1)] for i in xrange(2,n+1)];
	m = randint(0,n-1);
	E = sample(E,m);
	q = randint(1,MAXA);
	f.write("%d %d %d\n"%(n,m,q));
	for e in E:
		f.write("%d %d\n"%(e[0],e[1]));
	for _ in xrange(q):
		f.write("%d %d\n"%(randint(1,n),randint(1,n)));
	f.close();
	
def run():
	system("./test > out.out");
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
