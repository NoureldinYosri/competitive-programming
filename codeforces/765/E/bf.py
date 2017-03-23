G = [];
ans = 10**10;
root = None;

def dfs(u,p):
	global root;
	S = set();
	for v in G[u]:
		if v != p:
			R = dfs(v,u);
			if R[0]:
				S.add(R[1] + 1);
			else:
				return [0,0];
	if len(S) == 1:
		
n = int(raw_input());
G = [[] for i in xrange(n+1)];
for i in xrange(n-1):
	a,b = map(int,raw_input().split());
	G[a].append(b);
	G[b].append(a);
