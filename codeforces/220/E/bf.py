def cnt(A):
	n = len(A);
	ret = 0;
	for i in xrange(n):
		for j in xrange(i):
			ret += A[j] > A[i];
	return ret;


def solve(A,k):
	n = len(A);
	for r in xrange(n):
		for l in xrange(r):
			if cnt(A[:(l+1)] + A[r:]) <= k:
				print l,r;


n,k = map(int,raw_input().split());
A = map(int,raw_input().split());
solve(A,k);
