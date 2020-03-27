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

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(const pi & p) const {
		uint64_t x = p.first;
		x = (x << 32) | p.second;
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};


const int MAXN = 2000+2;
unordered_map<pi, int, custom_hash> dp[MAXN];
int n, m;
int L[MAXN], S[MAXN];
int C[2*MAXN];

int f(int x, int & c, int lim){
//	cerr << x << " " << c << " " << lim << " -> ";
	int ret = 0;
	for(; c && x < lim; ){
		ret += c * C[x];
		x++;
		c >>= 1;
	}
	if(x != lim) c = 0;
//	cerr << ret << " " << c << endl;
	return ret;
}

int solve(int i, int low, int cnt){
	if(i == -1) return f(low, cnt, INT_MAX);
	pi t(low, cnt);
	if(dp[i].count(t)) return dp[i][t];
	dp[i][t] = solve(i-1, low, cnt);
	if(L[i] < low) return dp[i][t];
	if(L[i] == low) dp[i][t] = max(dp[i][t], solve(i-1, low, cnt + 1) - S[i]);
	else {
		int tmp = f(low, cnt, L[i]);
		dp[i][t] = max(dp[i][t], solve(i-1, L[i], cnt + 1) - S[i] + tmp);
	}
	return dp[i][t];
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, n) scanf("%d", L + i);
	loop(i, n) scanf("%d", S + i);
	for(int x = 1; x <= n+m; x++) scanf("%d", C + x);
	
	cout << solve(n-1, 1, 0) << endl;
	return 0;
}
