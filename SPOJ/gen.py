from random import randint;

f = file("in.in","w");
N = 4000;

f.write(str(N) + "\n");
for i in range(N):
	f.write(str(2**52 - 1) + "\n");

