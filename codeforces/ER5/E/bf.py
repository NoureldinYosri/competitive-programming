def g(n,m):
	ans = 0;
	for i in xrange(1,m + 1): ans += n%i;
	return ans;

n,m = map(int,raw_input().split());
print g(n,m);
