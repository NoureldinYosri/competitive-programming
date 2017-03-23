from random import *;
from string import *;
from os import system;

MAXN = 100;
MAXM = 100;
MAXA = 10;

def randomize(A):
	ret = "";
	for a in A:
		ret += choice(".,!? ");
		if len(ret) == 100: break;
		if len(ret) + len(a) > 100: break;
		ret += a;
	ret += choice(".,!? ");
	return ret;

def create_test():
	f = file("in.in","w");
	T = 1;
	f.write("%d\n"%T);	
	for t in xrange(T):
		n = randint(1,MAXN);
		m = randint(1,MAXM);
		names = ["".join([choice(lowercase) for i in xrange(randint(1,MAXA))]) for j in xrange(n)];
		names = list(set(names));
		n = len(names);
		f.write("%d\n"%n);
		for name in names:
			f.write("%s "%name);
		f.write("\n%d\n"%m);
		for i in xrange(m):
			t = choice([0,1]);
			shuffle(names);
			if t: f.write("%s:"%names[0]);
			else: f.write("?:");
			f.write("%s\n"%randomize(names[t:]));
	f.close();
		
def run():
	system("./test < in.in > out.out");
	system("./AC < in.in > correct.out");


def is_correct():
	f = file("out.out");
	F = [l for l in f];
	f.close();
	f = file("correct.out");
	G = [l for l in f];
	f.close();
	x = "Impossible" in F[0];
	y = "Impossible" in G[0];
	return not (x ^ y);

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
