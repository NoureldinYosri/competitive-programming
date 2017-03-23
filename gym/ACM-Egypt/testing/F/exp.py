def f(n):
	s = 0;
	while n:
		s += n;
		n /= 10;
	return s;


S = set();
mx = 0;
l = 0;c = 1;
for i in xrange(1,50 + 1):
	s = f(i);
	if c and l > s: 
		print "not"
		c = 0;
	print s;
	l = s;

