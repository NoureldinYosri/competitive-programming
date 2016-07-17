from random import *;
from os import *;

MAXN = 5;
MAXM = 5;

def create_test():
	f = file("in.in","w");

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
