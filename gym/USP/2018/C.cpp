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


const int MAX = 1 << 20;

vi primes;
vector<pair<ll,int> > f;
int isPrime[MAX];
vi E;

void sieve(){
	for(int i = 2;i < MAX;i++) isPrime[i] = 1;
	for(int i = 2;i < MAX;i++)
		if(isPrime[i]) {
			primes.push_back(i);
			for(ll j = i*(ll)i;j < MAX;j += i)
				isPrime[j] = 0;
		}
//	cout << sz(primes) << endl;
}

const int mod = 1e9 + 7;
vector<vi> dp;
int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

vi divs;

int solve(int i,int b) {
	if(b == 1) return 1;
	if(i == -1) return 0;
	int & ret = dp[i][b];
	if(ret != -1) return ret;
	ret = 0;
	for(int e1 : divs){
		int e = e1 - 1;
		if(e > E[i]) break;
		if(b%(e+1) == 0)
			ret = add(ret,solve(i-1,b/(e+1)));
	}
	return ret;
}

int B,n;
ll A[1 << 20];

int solve(){
	loop(i,n){
		ll x = A[i];
		for(auto p : primes) {
			if(x < p*(ll)p) break;
			if(x%p) continue;
			int e = 0;
			while(x%p == 0) x /= p,e++;
			f.emplace_back(p,e);
		}
		if(x > 1) f.emplace_back(x,1);
	}
	sort(all(f));
	for(int i = 0;i < sz(f);) {
		int j = i;
		int s = 0;
		ll p = f[i].first;
		while(j < sz(f) && p == f[j].first) {
			s += f[j].second;
			j++;
		}
		E.push_back(s);
		i = j;
	}
	sort(all(E));
	reverse(all(E));
	dp = vector<vi>(sz(E),vi(B+1,-1));
	for(int i = 1;i <= B;i++)
		if(B%i == 0)
			divs.push_back(i);
	return solve(sz(E)-1,B);
}

void read(){
	scanf("%d %d",&B,&n);
	loop(i,n) scanf("%lld",A + i);
}

void gen(){
	B = rand()%10 + 1;
	n = rand()%5 + 1;
	loop(i,n) A[i] = rand()%10 + 2;
}

//int bf(){
//	return bt(n-1,)
//}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	sieve();
	read();
	cout << solve() << endl;
	return 0;
}
#endif
