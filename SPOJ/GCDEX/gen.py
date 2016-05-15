def gcd(a,b):
	while b: a,b = b,a%b;
	return a;

n = 50;
l = len(str(n));
for i in xrange(n):
	for j in xrange(n):
		m = gcd(i,j); m = str(m);
		m = (l - len(m)) * ' ' + m;
		print m,;
	print ;
