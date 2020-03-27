#pragma GCC optimize ("O3")
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


const int mod = 998244353;

int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}

const int MAX = 500*1000 + 10;
int n, K, m;
int L[MAX], R[MAX], X[MAX];
int cnt[MAX];
int val[MAX];

int tail[MAX];
int p2[MAX];
int dp[MAX], sum[MAX];
int prv[MAX], nxt[MAX];

int solve(int b){
	static vp V;
	loop(i, n+1) cnt[i] = 0;  
	V.clear();
	loop(i, m){
		int x = (X[i] >> b) & 1;
		if(x){
			cnt[L[i]] ++;
			cnt[R[i]+1] --;
		}
		else {
			V.emplace_back(L[i], R[i]);
		}
	}
	for(int i = 1; i <= n;i++){
		cnt[i] += cnt[i-1];
		val[i] = (cnt[i] > 0) + val[i - 1];
	}
	for(int i = 1, v = -1; i <= n; i++){
		if(!cnt[i]) v = i;
		prv[i] = v;
	}
	for(int i = n, v = -1; i >= 1; i--){
		if(!cnt[i]) v = i;
		nxt[i] = v;
	}
//	prArr(prv, n + 1, int);
//	prArr(nxt, n + 1, int);
	for(int i = 1; i <= n; i++) tail[i] = -1;
	for(auto p : V){
		int l = p.first, r = p.second;
		int ctr = val[r] - val[l-1];
		if(ctr == r-l+1) return 0;
		l = nxt[l];
		r = prv[r];
		l = l-val[l];
		r = r-val[r];
//		cerr << p << " " << l << " " << r << endl;
		tail[r] = max(tail[r], l);
	}
	
	int m = n - val[n];
	if(!m) return 1;

//	cerr << "m = " << m << endl;
//	prArr(tail, m+1, int);
	
	dp[0] = 1;
	sum[0] = 1;
	int L = 0;
	for(int i = 1; i <= m; i++){
		dp[i] = add(sum[i-1], L ? -sum[L-1] : 0);
		sum[i] = add(dp[i], sum[i-1]);
		L = max(L, tail[i]);
	}
	
//	prArr(dp, m+1, int);
	int ret = add(sum[m], L ? -sum[L-1] : 0);
//	cerr << b << ": " << ret << endl;
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	p2[0] = 1;
	for(int i = 1; i < MAX;i ++)
		p2[i] = mul(2, p2[i-1]);
	scanf("%d %d %d", &n, &K, &m);
	loop(i, m) scanf("%d %d %d", L + i, R + i, X + i);
	int ans = 1;
	loop(b, K){
		ans = mul(ans, solve(b));
		if(!ans) break;
	}
	cout << ans << endl;
	return 0;
}
