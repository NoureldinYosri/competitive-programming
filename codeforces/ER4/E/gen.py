from random import randint;

f = file("in.in","w");
n = randint(1,10);
f.write(str(n) + "\n");
S = [i + 1 for i in xrange(n)]
for i in xrange(n):
	j = randint(0,n - 1 - i);
	f.write(str(S[j]) + "\n");
	S.pop(j);
f.close();
