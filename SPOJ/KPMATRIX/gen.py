from random import randint;

f = file("randinput.in","w");

N = 250; M = int(1e9);
f.write("250 250\n");
for i in range(N):
	for j in range (N):
		f.write(str(randint(-M,M)) + " ");
	f.write("\n");
f.write(str(randint(-M,M)) + "\n");
