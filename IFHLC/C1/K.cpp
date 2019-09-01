#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

const int MAXX = 5000 + 10;
const int mod = 1e9 + 7;
int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b) {
	return (a*(ll)b)%mod;
}


int len[300],top[300],bottom[300];

int dp[200][MAXX];
int dp2[200][MAXX][2][2];


int solve(int i,int x,int tp,int lft) {
	if(i == 1) {
		int in = tp || lft;
		int isInd = !in;
		return x - isInd == 0;
	}
	int & ret = dp2[i][x][tp][lft];
	if(ret != -1) return ret;
	ret = 0;
	loop(dwn,2) {
		int in = tp || (1 - dwn);
		int isInd = !in;
		if(x - isInd < 0) continue;
		ret = add(ret,solve(i-1,x-isInd,dwn,lft));
	}
	return ret;
}


int solve2(int k,int x) {
	if(len[k] < x) return 0;
	return solve(len[k],x,top[k-1],bottom[k-1]);
}

int solve(int k,int x) {
	if(k == 0) return x == 1;
	int & ret = dp[k][x];
	if(ret != -1) return ret;
	ret = 0;
	for(int i = 0;i <= x && i <= len[k];i++)
		ret = add(ret,mul(solve(k-1,x-i),solve2(k,i)));
	return ret;
}

int solve(int n,int m,int x) {
	if(x >= MAXX) return 0;
	int k = 0;
	loop(i,n) loop(j,m) {
		len[i+j]++;
		top[i+j] |= j==m-1;
		bottom[i+j] |= i==n-1;
		k = max(k,i+j);
	}
	memset(dp,-1,sizeof dp);
	memset(dp2,-1,sizeof dp2);
	return solve(k,x);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n,m,x; cin >> n >> m >> x;
	cout << solve(n,m,x) << endl;
	return 0;
}
