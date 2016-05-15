from random import randint;

f = file("in.in","w");

t = randint(1,100);
m = randint(1,100);
f.write(str(t) + " " + str(m) + "\n");

for i in range(m):
	f.write(str(randint(1,t)) + "\n");
