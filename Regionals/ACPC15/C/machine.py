from random import randint;

n = 4;
inf = file("in.in","w");
ouf = file("correct.out","w");
inf.write("1\n" + str(n) + " " + str(n) + "\n");
F = [[0 ,0] for i in range(n)];
for i in range(n):
	for j in range(2):
		F[i][j] = randint(-10,10);
		inf.write(str(F[i][j]) + " ");
	inf.write("\n");
for i in range(n):
	X = [0 ,0]
	for j in range(2):
		X[j] = randint(-10,10);
		inf.write(str(X[j]) + " ");
	inf.write("\n");
	ans = -(1 << 64);
	for j in range(n):
		ans = max(ans,X[0] * F[j][0] + X[1] * F[j][1]);
	ouf.write(str(ans) + "\n");

inf.close();
ouf.close();
