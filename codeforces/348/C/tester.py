from random import *;
from string import *;
from os import system;

MAXN = 5;
MAXM = 5;
MAXA = 5;

def create_test():
	f = file("in.in","w");
	n = 10**5;
	m = 200;
	f.write("%d %d 0\n"%(n,m));
	S = [0 for i in xrange(m)];
	s = 10**5;
	for i in xrange(m):
		S[i] = randint(1,s - (m - i - 1));
		s -= S[i];
	if sum(S) > 10**5: 
		print "no";
		return;
	A = [i+1 for i in xrange(n)];
	for i in xrange(m):
		f.write("%d "%S[i]);
		idx = A[:min(2*S[i],n)];
		shuffle(idx);
		idx = idx[:S[i]];
		idx = [str(x) for x in idx];
		idx = " ".join(idx);
		f.write("%s\n"%idx);
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
		break;
		run();
		if not is_correct():
			print "found";
			break;
		print "done with %d"%i;
		i += 1;

if __name__ == "__main__":
	main();
