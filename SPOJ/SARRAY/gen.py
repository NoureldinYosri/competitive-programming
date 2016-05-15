from random import *;
from string import *;
from os import *;

MAX = 5;
def genTest():
	f = file("in.in","w");
	for i in xrange(3):
		for j in xrange(randint(1,MAX)):
			c = 'a'; #choice(lowercase)
			f.write(c);
		f.write("\n");
	f.close();
	
def judge():
	system("./test < in.in > out.out");
	system("./AC < in.in > AC.out");
	system("diff AC.out out.out > e.out");
	f = file("e.out");
	f = [line for line in f];
	return len(f) == 0;

t = 1
while 1:
	genTest();
	if not judge(): 
		print "found";
		break;
	print t;
	t += 1;
