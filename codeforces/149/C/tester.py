from random import *;
from os import *;

MAXN = 5;
MAXM = 5;
MAXA = 5;

def get_pair():
	x = randint(1,MAXA);
	y = randint(x,MAXA);
	return [x,y];


def create_test():
	f = file("in.in","w");
	X,Y = get_pair(),get_pair();
	f.write("%d %d %d %d\n"%(X[0],X[1],Y[0],Y[1]));
	n = randint(1,MAXM);
	f.write("%d\n"%(n + 2));
	f.write("%d %d %d\n"%(X[0],X[1],X[1]));
	f.write("%d %d %d\n"%(Y[0],Y[1],Y[1]));
	for i in xrange(n):
		t = get_pair();
		f.write("%d %d %d\n"%(randint(1,MAXA),t[0],t[1]));
	f.close();
	
def run():
	system("./test < in.in > out.out");
	system("./AC < in.in > AC.out");	

def is_correct():
	system("diff out.out AC.out > err.log");
	F = file("err.log","r");
	F = [l for l in F];
	return len(F) == 0;

def get(w):
	f = file(w,"r");
	f = [l for l in f];
	return int(f[0]);

def main():
	t = 1;
	while True:
		create_test();
		run();
		if not is_correct():
			print "found";
			print "correct : %d"%get("AC.out");
			print "found : %d"%get("out.out");
			break;
		print "done with %d"%t;
		t += 1;

if __name__ == "__main__":
	main();
