from random import *;
from string import *;
from os import system;
import numpy as np;

MAXN = 50;
MAXM = 5;
MAXA = 5;

def create_test():
	f = file("in.in","w");
	n = randint(2,MAXN);
	S = [np.random.choice(np.array([c for c in lowercase[:2]]),randint(1,MAXM),True) for i in xrange(randint(1,MAXN))];
	nxt = [[-1 for i in xrange(26)]];
	E = [];
	for s in S:
		cur = 0;
		for c in s:
			idx = ord(c) - ord('a');
			if nxt[cur][idx] == -1:
				nxt[cur][idx] = len(nxt);
				nxt.append([-1 for i in xrange(26)]);
				E.append([cur + 1,nxt[cur][idx] + 1,c]);
			cur = nxt[cur][idx];
		if len(nxt) >= n: break;
	f.write("%d\n"%len(nxt));
	for e in E:
		f.write("%d %d %c\n"%(e[0],e[1],e[2]));	
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
