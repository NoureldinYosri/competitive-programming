dp = {};
primes = [];

def solve(n,p):
	if dp.has_key([n,p]):
		return dp[[n,p]];
	ans = 0;	
	for i in range(1,n + 1):
		P = p;
		for j in range(len(primes)):
			k = n;
			while k%primes[j] == 0:
				P[j] += 1;
		ans += solve(n - i,P);
	d[[n,p]] = ans;
	return ans;
		

#l = 0;
#ll = 0;
#lll = 0;
#for n in range(1,25):
#	S = [];	
#	solve(n,1);
#	f = len(set(S));
#	print n,f,f - l,f - 2*l + ll,f - 2*l + ll - (l - 2*ll + lll);
#	lll = ll;	
#	ll = l;	
#	l = f;

for i in range(2,71):
	c = 1;
	j = 2;
	while j*j <= i and c:
		if i%j == 0:
			c = 0;
		j += 1;
	if c:
		primes.append(i);
print solve(10,[0 for i in range(len(primes))]);
