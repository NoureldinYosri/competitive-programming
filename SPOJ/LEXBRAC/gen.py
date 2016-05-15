dp = [[[-1 for i in xrange(300)] for j in xrange(300)] for k in xrange(300)]
D = [[1,0],[-1,0],[0,1],[0,-1]];
out = ['(',')','[',']'];

N = int(raw_input());
K = int(raw_input());

def solve(i,j,k):
	global D,N,K;
	if i == N: return j == 0 and k == 0;
	if i < 0 or j < 0: return 0;
	if dp[i][j][k] != -1: return dp[i][j][k];
	dp[i][j][k] = 0;
	for q in xrange(4):
		d = D[q];
		dp[i][j][k] += solve(i + 1,j + d[0],k + d[1]);
	return dp[i][j][k];


s = "";
j = k = 0;
for i in xrange(N):
	u = tot = 0;
	for q in xrange(4):
		u = tot;
		tot += solve(i + 1,j + D[q][0],k + D[q][1]);
		if tot >= K: break;
	s += out[q];
	K -= u;
	j,k = j + D[q][0],k + D[q][1];
print s;
