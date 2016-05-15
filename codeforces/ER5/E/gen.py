import os;
from random import randint;

def g(n,m):
	ans = 0;
	for i in xrange(1,m + 1): ans += n%i;
	return ans;

while True:
	n,m = randint(1,20),randint(1,20);
	f = file("in.in","w");
	f.write(str(n) + " " + str(m) + "\n");
	f.close();
	os.system("./test < in.in > out.out");
	f = file("out.out","r");
	F = [line for line in f];
	f.close();
	if int(F[0]) != g(n,m) : 
		print "NOOOOOOOOOO";
		break;
	
