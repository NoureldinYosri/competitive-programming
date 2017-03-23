from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 5;
MAXA = 5;

def create_test():
	f = file("in.in","w");
	n = randint(1,MAXN);
	f.write("%d\n"%n);
	for i in xrange(n):
		x1 = randint(-MAXA,MAXA);
		y1 = randint(-MAXA,MAXA);
		x2 = randint(-MAXA,MAXA);
		y2 = randint(-MAXA,MAXA);
		if choice([0,1]): x1 = x2;
		else: y1 = y2;
		f.write("%d %d %d %d\n"%(x1,y1,x2,y2));
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
