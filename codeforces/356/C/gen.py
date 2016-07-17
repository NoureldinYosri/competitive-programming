def f(n):
	m = int(n**(1.0/3)) + 10;
	ctr = 0;
	while n > 0:
		while m*m*m > n: m -= 1;
		n -= m*m*m;
		ctr += 1;
	return ctr;


s = 0
for i in xrange(1,10**5):
	s += f(i)

print s;

