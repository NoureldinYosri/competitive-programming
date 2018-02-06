n = int(raw_input());
C = map(int,raw_input().split());
Q = [n-1-i for i in xrange(n)];
cnt = [0 for i in xrange(n)];
S = set();
while tuple(Q) not in S:
	# print Q;
	S.add(tuple(Q));
	f = Q.pop();
	c = C[f];
	cnt[f] += 1;
	Q = Q[:c] + [f] + Q[c:];

L = [];
ans = 0;
for i in xrange(n):
	if cnt[i] == 0:
		L.append(i);
	ans += cnt[i] == 0;
print L;
print ans;