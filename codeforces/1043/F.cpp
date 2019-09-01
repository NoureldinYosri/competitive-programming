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


const int MAXA = 300*1000;
int A[1 << 20],n;
int prime[MAXA + 1];
vi P[1 << 20];
int f[MAXA + 1],cf[MAXA + 1];
int skip[MAXA + 1];
int dp[MAXA + 1];

void sieve(){
	for(int i = 2;i <= MAXA;i++) {
		if(prime[i] == 0) {
			prime[i] = i;
			for(ll j = i*(ll)i;j <= MAXA;j += i)
				prime[j] = i;
		}
		int x = i;
		while(x > 1) {
			int p = prime[x];
			P[i].push_back(p);
			x /= p;
			while(x%p == 0) x /= p,skip[i] = 1;
		}
	}
}

int mem[MAXA + 1];

void process(int x){
	const vi & P = ::P[x];
	int m = sz(P);
	int tot = 1 << m;
	for(int msk = 0;msk < tot;msk++) {
		int y = 1,aux = msk;
		loop(i,m) {
			int r = aux & 1; aux >>= 1;
			if(r) y *= P[i];
		}
 		cf[y]++;
	}
}

int check(int x) {
	if(x == 1) return 0;
	int  & res = mem[x];
	if(res != -1) return res;
	res = 0;
	const vi & P = ::P[x];
	int m = sz(P);
	int tot = 1 << m;
	for(int msk = 0;msk < tot;msk++) {
		int y = 1,sgn = 1,aux = msk;
		loop(i,m) {
			int r = aux & 1; aux >>= 1;
			if(r) y *= P[i],sgn *= -1;
		}
		res += cf[y]*sgn;
	}
	assert(res >= 0 && res <= n);
	return res;
}

int solve(){
	int g = 0;
	loop(i,n) g = __gcd(A[i],g);
	if(g != 1) return -1;

	sort(A,A + n);
	n = unique(A,A + n) - A;
	if(A[0] == 1) return 1;
	loop(i,n) {
		int x = A[i],y = 1;
		while(x > 1) {
			int p = prime[x];
			while(x%p == 0) x /= p;
			y *= p;
		}
		if(!f[y]){
			f[y] = 1;
			process(y);
		}
	}
	n = 0;
	for(int x = 2;x <= MAXA;x++)
		n += f[x];
	dp[1] = 0;
	memset(mem,-1,sizeof mem);
	int ans = INT_MAX;
	for(int x = 2;x <= MAXA;x++) if(!skip[x]){
		dp[x] = 1 << 29;
		for(int msk = 0;msk < (1 << sz(P[x]));msk++) {
			int y = 1;
			loop(i,sz(P[x])) if((msk >> i) & 1) y *= P[x][i];
			if(check(x/y)) dp[x] = min(dp[x],dp[y] + 1);
		}
//		if(x <= 15) cerr << x << ": " << dp[x] << endl;
		if(f[x]) {
//			cerr << x << " " << dp[x] + 1 << endl;
			ans = min(ans,dp[x] + 1);
		}
	}
	return ans;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	sieve();
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	printf("%d\n",solve());
	return 0;
}
