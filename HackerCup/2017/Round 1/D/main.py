mod = 10**9 + 7;
MAX = 2000*2000 + 1;
f = [1 for i in xrange(MAX)];
r = [1 for i in xrange(MAX)];
for i in xrange(MAX - 1):
	f[i + 1] = (f[i] * (i + 1))%mod;
	r[i + 1] = pow(f[i + 1],mod - 2,mod);


def C(n,k):
	if k > n or n < 0: return 0;
	ret = 1;
	for i in xrange(k):
		ret *= (n-i);
		ret %= mod;
	ret *= r[k];
	ret %= mod;
	return ret;

def g(n,k):
	if k < 0: return 0;
	return C(n + k - 1,k);

T = int(raw_input());
for t in xrange(1,T + 1):
	n,m = map(int,raw_input().split());
	s = 0;
	A = [0 for i in xrange(n)];
	for i in xrange(n):
		A[i] = int(raw_input());
		s += A[i];
	S = xrange(-1,n);
	ans = 0;
	for i in xrange(n):
		for j in xrange(n):
			if i != j:
				q = s - A[i] - A[j];
				q = m - 2*q - q - A[i] - A[j];
				tmp = g(n+1,q);
		#		print i,j,q,tmp;
				ans += tmp*f[n-1]; 
				ans %= mod;
	ans *= r[2];
	ans %= mod;	
	print ans;
