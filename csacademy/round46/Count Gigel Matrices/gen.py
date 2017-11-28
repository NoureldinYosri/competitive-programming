from random import *;

f = file("in.in","w");
f.write("2000 2000\n");
for i in xrange(2000):
	s = "".join([choice("1") for j in xrange(2000)]);
	f.write("%s\n"%s);
f.close();