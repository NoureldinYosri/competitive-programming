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

int n,K;
ll P;
int A[1 << 20];
ll dp[1 << 20];

ll solve(int i){
	if(i < 0) return 0;
	ll & ret = dp[i];
	if(ret != -1) return ret;
	ret = solve(i-1) + A[i];
	if(i+1 >= K) ret = min(ret,solve(i-K) + A[i]);
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %lld %d",&n,&P,&K);
		loop(i,n) scanf("%d",A + i);
		sort(A,A + n);
		fill(dp,dp + n,-1);
		int ans = 0;
		for(int i = 0;i < n;i++)
			if(solve(i) <= P)
				ans = i+1;
		printf("%d\n",ans);
	}
	return 0;
}
