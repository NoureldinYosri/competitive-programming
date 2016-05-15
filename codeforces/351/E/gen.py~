from random import *;
import os;
MAXN = 2*10**5;
MAXK = 50;
MAX = 10**5;

def genTest(f):
	n = MAXN; #randint(1,MAXN);
	k = 50; #randint(1,MAXK); k = min(n,50);
	f.write(str(n) + " " + str(k) + "\n");
	for i in xrange(n): f.write(str(MAX) + " ");

t = 1;
while 1:
	f = file("in.in","w");
	genTest(f);
	f.close();
	os.system("./test < in.in > out.out");
	os.system("./AC < in.in > AC.out");
	f = file("out.out");
	x = [float(line) for line in f][0];
	f.close();
	f = file("AC.out");
	y = [float(line) for line in f][0];
	f.close();
	if abs(x - y)/max(1,y) > 1e-4 : 
		print "found";
		break;
	print t;
	t += 1;
