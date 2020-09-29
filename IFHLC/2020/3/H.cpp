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

const int MAXN = 111;
int n;
int A[MAXN];
int f[MAXN][MAXN];
int dp[MAXN];


void tc(){
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	static vi LIS;
	for(int s = 0; s < n; s++){
		LIS.clear();
		for(int e = s; e < n; e++){
			int x = A[e];
			if(LIS.empty() || x > LIS.back()) LIS.pb(x);
			else *lower_bound(all(LIS), x) = x;
			f[s][e] = sz(LIS);
		}
	}
	
	for(int k = 1; k <= n; k++){
		dp[n] = 0;
		for(int s = n-1; s >= 0; s--){
			dp[s] = dp[s+1];
			for(int e = s; e < n; e++) if(f[s][e] >= k) {
				dp[s] = max(dp[s], f[s][e] + dp[e+1]); 
			}
		}
		printf("%d ", dp[0]);
	}
	
	puts("");
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
