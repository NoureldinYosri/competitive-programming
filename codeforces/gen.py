from random import randint;

f = file("in.in","w");

n = 1000;

f.write(str(1000) + "\n");
for i in range(n):
	f.write(str(randint(1,int(1000))) + "\n");

