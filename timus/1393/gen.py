import os;
from random import randint,choice;
from string import lowercase as alpha

def genTest():
	ret = "";
	n = ranint(1,10);
	ret += str(n) + "\n";
	for i in xrange(n):
		ret += choice[alpha];
	ret += "\n";
	return ret;

while True:
	f = file("in.in","w");
	f.write(genTest);
	
