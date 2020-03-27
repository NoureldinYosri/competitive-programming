#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;


const int MAX = 100*1000 + 10;
int A[MAX],n,mod;
vi P;
int notPrime[MAX];

void sieve(){
	for(int i = 2;i < MAX;i++)
		if(notPrime[i] == 0) {
			P.pb(i);
			for(ll j = i*1LL*i;j < MAX;j += i)
				notPrime[j] = 1;
		}
}

int getPhi(int m) {
	int n = m, phi = n;
	for(int p : P){
		if(p*p > n) break;
		if(n%p) continue;
		phi -= phi / p;
		while(n%p == 0) n /= p;
	}
	if(n > 1) phi -= phi/n;
	return phi;
}


int mul(int a,int b,int m) {
	a %= mod,b %= mod;
	return (a*1LL*b)%m;
}

int add(int a,int b,int m) {
	a %= mod,b %= mod;
	a += b;
	if(a >= m) a -= m;
	if(a < 0) a += m;
	return a;
}

int powmod(int x,int p,int m) {
	x %= m;
	if(!p) return 1%m;
	int y = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) y = mul(x,y,m);
		x = mul(x,x,m);
	}
	return mul(x,y,m);
}


int solve(int l, int r, int mod){
	if (mod == 1) return 0;
	if(l == r) return A[l]%mod;
	int x = A[l];
	int g = __gcd(x, mod);
	return g*powmod(x/g, solve(l+1, r, getPhi(mod/g)), mod);
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	sieve();
	scanf("%d %d",&n,&mod);
	range(i,1,n) scanf("%d",A + i);

	int Q; scanf("%d",&Q);
	for(int q = 1;q <= Q;q++) {
		int l,r; scanf("%d %d",&l,&r);
		printf("%d\n", solve(l, r, mod));
	}
	return 0;
}
