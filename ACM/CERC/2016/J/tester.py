from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 5;
MAXA = 5;

def create_test():
	f = file("in.in","w");
	n = randint(2,MAXN);
	l = 0;
	d = randint(2,MAXM);
	A = [];
	for i in xrange(d):
		C = [j for j in xrange(1,n + 1)];
		if l in C: C.remove(l)
		A.append(choice(C));
		l = A[-1];
	if A[-1] != A[0]: A.append(A[0]);
	f.write("%d %d\n"%(n,len(A)));
	f.write("%s\n"%(" ".join([str(x) for x in A])));
	E = [];
	for i in xrange(len(A) - 1):
		a = A[i];
		b = A[i + 1];
		E.append([a,b,choice(['O','R']),randint(1,MAXA)]);
	m = randint(1,MAXM);
	for i in xrange(m):
		a = randint(1,n);
		b = 1;
		if a != n : b = randint(a + 1,n);
		else : b = randint(1,a - 1);
		E.append([a,b,choice(['O','R']),randint(1,MAXA)]);
	f.write("%d\n"%len(E));
	for e in E:
		f.write("%d %d %c %d\n"%(e[0],e[1],e[2],e[3]));
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
