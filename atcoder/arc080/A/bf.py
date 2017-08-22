import itertools
n = int(raw_input())
A = map(lambda s:int(s)%4,raw_input().split());
A.sort();

for B in itertools.permutations(A):
	cond = True;
	for i in xrange(n-1):
		if (B[i]*B[i + 1])%4:
			cond = False;
	if cond: 
		print "Yes";
		exit(0);
print "No";
