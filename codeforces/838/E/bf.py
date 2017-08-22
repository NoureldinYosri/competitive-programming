import itertools
from math import sqrt;

n = int(raw_input().split())
X = [0 for i in xrange(n)];
Y = [0 for i in xrange(n)];
for i in xrange(n):
	X[i],Y[i] = map(int,raw_input().split());


def intersect(a,b,c,d):
	if a > b: a,b = b,a;
	if c > d: c,d = d,c;
	if (a in [c,d]) or (b in [c,d]): return 0;
	if (c in [a,b]) or (d in [a,b]): return 0;
	if a == b or c == d: return 0;
	def ccw(o,u,v):
		x1 = X[u] - X[o];
		x2 = X[v] - X[o];
		y1 = Y[u] - Y[o];
		y2 = Y[v] - Y[o];
		return x1*y2 - x2*y1;
	def sgn(v):
		assert v != 0;
		return (v > 0) - (v < 0);
	s1,s2 = sgn(ccw(a,b,c)),sgn(ccw(a,b,d));
	s3,s4 = sgn(ccw(c,d,a)),sgn(ccw(c,d,b));
	if s1 == s2 or s3 == s4: return 0;
	return 1;

def dist(a,b):
	dx = X[a] - X[b];
	dy = Y[a] - Y[b];
	return sqrt(dx**2 + dy**2);

ans = 0;
for P in itertools.permutations(range(n)):
	cond = 0;
	for i in xrange(n):
		for j in xrange(n):
			for a in xrange(n):
				for b in xrange(n):
					if intersect(P[i],P[j],P[a],P[b]):
						cond = 1;
	if cond: continue;
	tmp = 0;
	for i in xrange(n-1):
		a,b = P[i],P[i + 1];
		tmp += dist(a,b);
	ans = max(ans,tmp);

print "%.18f"%ans;
