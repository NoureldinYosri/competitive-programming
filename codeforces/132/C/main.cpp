#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

char com[111];
int dp [111][52][2][2];
int vis[111][52][2][2],L;

int solve(int p,int n,int dir,int ch){
	if(p == L) return (n == 0) ? 0 : -3000;
	if(vis[p][n][dir][ch]) return dp[p][n][dir][ch];
	vis[p][n][dir][ch] = 1;	
	int & ret = dp[p][n][dir][ch];
	bool c = com[p] == 'F'; c ^= ch;
	if(c){
		ret = solve(p+1,n,dir,0) + 1 - 2*dir;
		if(n) ret = max(ret,solve(p,n-1,dir,ch ^ 1));
	}
	else{
		ret = solve(p+1,n,dir^1,0);
		if(n) ret = max(ret,solve(p,n-1,dir,ch ^ 1));
	}
	return ret;
}

int solve2(int p,int n,int dir,int ch){
	if(p == L) return (n == 0) ? 0 : 3000;
	if(vis[p][n][dir][ch]) return dp[p][n][dir][ch];
	vis[p][n][dir][ch] = 1;	
	int & ret = dp[p][n][dir][ch];
	bool c = com[p] == 'F'; c ^= ch;
	if(c){
		ret = solve2(p+1,n,dir,0) + 1 - 2*dir;
		if(n) ret = min(ret,solve2(p,n-1,dir,ch ^ 1));
	}
	else{
		ret = solve2(p+1,n,dir^1,0);
		if(n) ret = min(ret,solve2(p,n-1,dir,ch ^ 1));
	}
	return ret;
}


int main(){
	int n;
	cin >> com >> n; L = strlen(com);
	int ans = solve(0,n,0,0);
	cerr << ans << endl;
	memset(vis,0,sizeof vis);
	ans = max(ans,-solve2(0,n,0,0));
	cerr << solve2(0,n,0,0) << endl;
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
