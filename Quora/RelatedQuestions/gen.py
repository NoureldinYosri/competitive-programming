from random import randint;

N = int(1e5);
P = [i for i in range(N + 1)];
W = [1 for i in range(N + 1)];

def find(a):
	if a == P[a]: return a;
	P[a] = find(P[a]);
	return P[a];

def connected(a,b):
	return find(a) == find(b);

def connect(a,b):
	a = find(a);
	b = find(b);
	if W[a] < W[b]: a,b = b,a;
	W[a] += W[b];
	P[b] = a;

f = file("randinput.in","w");
f.write(str(N) + "\n");
for i in range(N):
	f.write(str(randint(1,10))+ " ");
f.write("\n");
for i in range(N - 1):
	c = 1;
	a = b = 1;
	while c:
		a = randint(1,N);
		b = randint(1,N);
		c = connected(a,b);
	connect(a,b);
	f.write(str(a) + " " + str(b) + "\n");
