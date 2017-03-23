def func(A,B):
	n = len(A);
	m = len(A[0]);
	r = 0;
	for i in xrange(n):
		for j in xrange(m):
			r += abs(ord(A[i][j]) - ord(B[i][j]));
	return r;

G = ["abcde",
	"eabcd",
	"deabc",
	"cdeab",
	"bcdea"]

Q = [];
C = [];
Z = [];
for i in xrange(3):
	f = raw_input().split();
	C.append(f.pop());
	Q.append(map(int,f));


dist = 0;
for i in xrange(3):
	x1,y1,x2,y2 = Q[i];
	x1 -= 1;
	y1 -= 1;
	T = [[c for c in r] for r in G];
	for x in xrange(x1,x2):
		for y in xrange(y1,y2):
			dist += abs(ord(G[x][y]) - ord(C[i]));
			T[x][y] = C[i];
	Z.append(["".join(r) for r in T]);
print dist;	

s = 0;
for i in xrange(3):
	s += func(Z[i],G);
print s;

