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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;


const ll oo = 1LL << 61;
const int MAXN = 1 << 20;
int A[MAXN],n;
ll del,change;

vi cand;

void getPrimes(int x){
	static unordered_set<int> done;
	if(done.count(x)) return;
	done.insert(x);
	for(int p = 2;p*p <= x;p++) {
		if(x%p == 0) cand.push_back(p);
		while(x%p == 0) x /= p;
	}
	if(x > 1) cand.push_back(x);
}

int prime;
ll dp[MAXN][3];
#define notUsed 0
#define isOpen 1
#define Closed 2

ll solve(int i,int state) {
	if(i == n) return 0;
	ll & ret = dp[i][state];
	if(ret != -1) return ret;
	ret = oo;
	int r = A[i]%prime;
	r = min(r,prime-r);
	switch (state){
	case notUsed:
		if(r <= 1) ret = min(ret,r*change + solve(i+1,notUsed));
		ret = min(ret,solve(i,isOpen));
		break;
	case isOpen:
		ret = min(ret,solve(i+1,isOpen) + del);
		ret = min(ret,solve(i+1,Closed) + del);
		break;
	default:
		if(r > 1) return oo;
		ret = r*change + solve(i+1,Closed);
	}
	return ret;
}

ll solve(int p) {
	prime = p;
	memset(dp,-1,sizeof dp);
	return solve(0,notUsed);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %lld %lld",&n,&del,&change);
	loop(i,n) scanf("%d",A + i);
	cand.push_back(2);
	cand.push_back(3);
	cand.push_back(5);
	cand.push_back(7);
	for(int v : vi{A[0],A[n-1]})
		for(int dv = -1;dv <= 1;dv++)
			getPrimes(v + dv);
	sort(all(cand));
	cand.resize(unique(all(cand)) - cand.begin());
//	print(cand,int);
	ll ans = LLONG_MAX;
	for(int p : cand) ans = min(ans,solve(p));
	printf("%lld\n",ans);
	return 0;
}
