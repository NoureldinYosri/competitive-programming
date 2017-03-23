from random import *;
from string import *;
from os import system;

MAXN = 3;
MAXM = 5;
MAXA = 5;
MAXK = 5;
MAXV = 5;
MAXL = 2;

def create_num(leading,base,L):
	A = [randint(0,base - 1) for i in xrange(L)];
	if not leading: A[0] = randint(1,base - 1);
	return A;

def create_test():
	f = file("in.in","w");
	n = randint(1,MAXN);
	m = 10;#randint(2,MAXM);
	k = randint(1,MAXK);
	f.write("%d %d %d\n"%(n,m,k));
	L = create_num(0,m,randint(1,MAXL-1));
	R = create_num(0,m,randint(len(L)+1,MAXL));
	f.write("%d"%len(L));
	for d in L: f.write(" %d"%d);
	f.write('\n');
	f.write("%d"%len(R));
	for d in R: f.write(" %d"%d);
	f.write('\n');
	
	for i in xrange(n):
		num = create_num(1,m,randint(1,MAXL));
		f.write("%d"%len(num));
		for d in num: f.write(" %d"%d);
		f.write(' %d\n'%randint(1,MAXV));
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
