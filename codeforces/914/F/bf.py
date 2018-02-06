S = list(raw_input());
m = int(raw_input());

def getLen(c,l,P,fail):
	while l > 0 and P[l] != c: l = fail[l - 1];
	if c == P[l]: l += 1;
	return l;

def buildFail(P):
	fail = [0 for i in xrange(len(P))];
	for i in xrange(1,len(P)):
		fail[i] = getLen(P[i],fail[i - 1],P,fail);
	return fail;

for _ in xrange(m):
	L = raw_input().split();
	# print L;
	t = L.pop(0);
	if t == '1':
		p,c = L;
		p = int(p) - 1;
		S[p] = c;
	else:
		l,r,s = L;
		l,r = map(int,[l,r]);
		s = list(s);
		ml = 0;
		ans = 0;
		fail = buildFail(s);
		for i in xrange(l-1,r):
			ml = getLen(S[i],ml,s,fail);
			if ml == len(s):
				ans += 1;
				ml = fail[-1];
		print ans;
