S = list(raw_input());
m = int(raw_input());

for _ in xrange(m):
	A = map(int,raw_input().split());
	t = A.pop(0);
	if t == 1:
		l,r = A;
		ans = 0;
		for i in xrange(l-1,r):
			for j in xrange(i+1,r):
				for k in xrange(j+1,r):
					if S[j] == S[k]:
						for l in xrange(k+1,r):
							ans += S[i] == S[l];
		print ans;
	else:
		p,d = A;
		p -= 1;
		d = str(d);
		S[p] = d;
