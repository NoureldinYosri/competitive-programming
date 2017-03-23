from random import *;
from string import *;
from os import system;

MAXA = 10000;
MAXS = 100
MAXR = 20
MAXW = 10
MAXP = 5

def create_test():
	f = file("in.in","w");
	f.write("2\n");
	for t in xrange(2):
		s = randint(1,MAXS);
		r = randint(1,MAXR);
		w = randint(1,MAXW);
		p = randint(1,MAXP);
		f.write("%d %d %d %d\n"%(s,r,w,p));
		A = [];	
		for i in xrange(s):
			x = y = None;
			cond = True;
			while cond:
				x = randint(-MAXA,MAXA);
				y = randint(-MAXA,MAXA);
				cond = False;
				for pos in A:
					cond |= (x - pos[0])**2 + (y - pos[1])**2 < r**2;
			A.append([x,y]);
			f.write("%d %d\n"%(x,y));
		for i in xrange(w):
			x1 = randint(-MAXA,MAXA);
			y1 = randint(-MAXA,MAXA);
			x2 = randint(-MAXA,MAXA);
			y2 = randint(-MAXA,MAXA);
			if x1 == x2 and y1 == y2: x1 += 1;
			f.write("%d %d %d %d\n"%(x1,y1,x2,y2));
		for i in xrange(p):
			f.write("%d %d\n"%(randint(-MAXA,MAXA),randint(-MAXA,MAXA)));
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
