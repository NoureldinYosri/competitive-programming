from random import randint;
f = file("randinput.in","w");
T = 200;
n = 5000;
f.write(str(T) + "\n");
for t in xrange(T):
	f.write(str(n) + "\n");
	for i in xrange(n):
		f.write(str(randint(-5000,5000)) + " " + str(randint(-5000,5000)) + "\n");
f.close();
