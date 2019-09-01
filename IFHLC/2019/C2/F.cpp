#ifdef ACTIVE
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

const int MAX = 2001,mod = 1e9 + 7;
vi divs[MAX];
int prime[MAX];

void sieve(){
	divs[1].push_back(1);
	for(int i = 2;i < MAX;i++) {
		if(!prime[i]) {
			prime[i] = i;
			for(int j = i*i;j < MAX;j += i)
				prime[j] = i;
		}
		int p = prime[i],n = i,e = 0;
		while(n%p == 0) n/=p,e++;
		for(int q = 1;e >= 0;q *= p,e--)
			for(int d : divs[n])
				divs[i].push_back(q*d);
	}
}

int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b) {
	return (a*(ll)b)%mod;
}


int dp[MAX][MAX];

int solve(int x,int m) {
	if(m == 1) return 1;
	int & ret = dp[x][m];
	if(ret != -1) return ret;
	ret = 0;
	for(int d : divs[x])
		ret = add(ret,solve(d,m-1));
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	sieve();
	memset(dp,-1,sizeof dp);
	int T; scanf("%d",&T);
	while(T--) {
		int n,m; scanf("%d %d",&n,&m);
		int ans = 0;
		for(int i = 1;i <= n;i++)
			 ans = add(ans,solve(i,m));
		printf("%d\n",ans);
	}
	return 0;
}
#endif
