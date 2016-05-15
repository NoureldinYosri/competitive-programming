from random import randint;

f = file("in.in","w");
T = randint(1,200);
f.write(str(T) + "\n");
for t in range(T):
	m = randint(1,10);
	n = randint(1,10);
	s = randint(1,100);
	c = randint(1,100);

	f.write(str(m) + " " + str(n) + " " + str(s) + " " + str(c) + "\n");
	for i in range(m + n):
		f.write(str(randint(1,1000)) + " " + str(randint(1,1000)) + "\n");
