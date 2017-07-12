from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 5;
MAXA = 5;

def create_test():
	f = file("in.in","w");
	n = 10**5; #randint(1,MAXN);
	m = 10**5; #randint(1,MAXM);
	E = [];
	for i in xrange(2,n+1):
		E.append([1,randint(1,i-1),i]);
	for i in xrange(m):
		E.append([randint(2,3),randint(1,n)]);
	shuffle(E);
	F = [];	
	ctr = 0;
	for e in E:
		if e[0] == 1: F.append(e);
		elif e[0] == 2: 
			ctr += 1;
			F.append(e);
		elif ctr: F.append(e + [randint(1,ctr)]);
	if len(F) > m: F = F[:m];
	m = len(F);
	f.write("%d %d\n"%(n,m));
	for e in F:
		f.write(" ".join([str(x) for x in e]));
		f.write("\n");
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