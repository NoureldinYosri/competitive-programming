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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int mod = 1000000007;
int x;
ll n;

vi primes;

void factor(){
	for(int i = 2;i*i <= x;i++){
		if(x%i) continue;
		primes.push_back(i);
		while(x%i == 0) x /= i;
	}
	if(x > 1) primes.push_back(x);
}

int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b){
	return (a*(ll)b)%mod;
}

int powmod(int x,ll p) {
	if(p == 0) return 1;
	int y = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) y = mul(x,y);
		x = mul(x,x);
	}
	return mul(x,y);
}

int solve(int p) {
	int res = 1;
	ll q = p;
	while(q <= n) {
		int tmp = powmod(p,(n/q)%(mod - 1));
		res = mul(res,tmp);
		if(p <= n/q)
			q *= p;
		else break;
	}
	return res;
}

int getQ(int m,int p) {
	int q = 1;
	while(m%(q*p) == 0) q *= p;
	return q;
}

int bf(int p){
	int res = 1;
	for(int m = 1;m <= n;m++)
		res = mul(res,getQ(m,p));
	return res;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> x >> n;
	factor();
	int ans = 1;
	for(int p : primes) {
		int g = solve(p);
		ans = mul(ans,g);
//		cout << p << " " << g << " " << bf(p) << endl;
	}
	cout << ans << endl;
	return 0;
}
#endif
