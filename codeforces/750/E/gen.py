from random import *

def gen_word(n):
	return "".join([choice("20167") for i in xrange(n)]);

MAXN = 10;
word = n = None;
dp = None;
def solve(p,c):
	if p == n: return (c != 4) * 10000;
	if dp[p][c] != -1: return dp[p][c];
	dp[p][c] = solve(p + 1,c) + 1;
	if word[p] == '6' :
		if c < 3: dp[p][c] = min(dp[p][c],solve(p + 1,c) );
	elif word[p] == '7':
		if c < 3: dp[p][c] = min(dp[p][c],solve(p + 1,c) );
		else: dp[p][c] = min(dp[p][c],solve(p + 1,4) );
	else:
		if c != 4: dp[p][c] = min(dp[p][c],solve(p + 1,c + (word[p] == "2017"[c]) ) );
		else: dp[p][c] = min(dp[p][c],solve(p + 1,c ) );
	return dp[p][c];

def sim():
	global n,word,dp;
	n = randint(1,MAXN);
	word = gen_word(n);
	dp = [[-1 for i in xrange(5)] for k in xrange(n + 1)];
	ans = solve(0,0);
	if ans >= 10**4: ans = -1;
	if ans == -1: return sim();	
	print word,ans;

sim();
