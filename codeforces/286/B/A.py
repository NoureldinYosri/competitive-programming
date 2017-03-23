def work(P,k):
	n = len(P);
	ret = [];
	for i in xrange(n/k):
		s = i*k;
		e = i*k + k;
		A = [x for x in P[s : e]]
		ret = ret + A[1:] + [A[0]];
	if n%k:
		s = n - n%k;
		e = n;
		A = [x for x in P[s : e]]
		ret = ret + A[1:] + [A[0]];
	return ret;



for n in xrange(2,20):
	P = [i+1 for i in xrange(n)]
	for k in xrange(1,n+1):
		P = work(P,k);
		for x in P:
			print "%2d"%x,
		print;
	print "==========================";
