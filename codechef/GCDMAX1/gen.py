from random import randint;

f = file("randinput.in","w");
N = 500000;

for i in range(randint(1,10)):
	f.write(str(N) + " " + str(randint(1,1000000)) + "\n");
	for j in range(N):
		f.write(str(randint(1,1000000)) + "\n");
