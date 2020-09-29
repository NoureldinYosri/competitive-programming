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


const int MAXR = 30;
const int MAX = 100*1000 + 10;
int A[MAX],n,mod;
vi P;
int notPrime[MAX];
ll R[MAX][MAXR];


void sieve(){
	for(int i = 2;i < MAX;i++)
		if(notPrime[i] == 0) {
			P.pb(i);
			for(ll j = i*1LL*i;j < MAX;j += i)
				notPrime[j] = 1;
		}
}

int getPhi(int m) {
	static unordered_map<int, int> mem;
	if(mem.count(m)) return mem[m];
	int n = m, phi = n;
	for(int p : P){
		if(p*p > n) break;
		if(n%p) continue;
		phi -= phi / p;
		while(n%p == 0) n /= p;
	}
	if(n > 1) phi -= phi/n;
	mem[m] = phi;
	return phi;
}



int mul(int a,int b,int m) {
	a %= m;
	b %= m;
	return (a*(ll)b)%m;
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

int lg(int x){
	int b = 0;
	while((1LL << b) < x) b++;
	return b;
}


int solve(int l, int r, int mod){
	if(l == r) return A[l]%mod;
	if(mod == 1) return 0;
	int x = A[l];
	int phi = getPhi(mod);
	int n = solve(l+1, r, phi);

	ll exact = R[l+1][min(r-l, MAXR) - 1];
//	cerr << l+1 << " is " << A[l+1] << "**" << min(r-l, MAXR-1) << ": " << exact << " vs " << lg(mod) << " " << phi << endl;
	if(exact >= lg(mod)) return powmod(x, n + phi, mod);		
	
	return powmod(x, n, mod);
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	sieve();
	scanf("%d %d",&n,&mod);
	range(i,1,n) scanf("%d", A + i);

	loop(j, MAXR) R[n+1][j] = 1;
	for(int i = n; i; i--) {
		R[i][0] = A[i];
		for(int j = 1; j < MAXR; j++) {
			if(A[i] == 1){
				R[i][j] = 1;
				continue;
			}
			ll e = R[i+1][j-1];
			if(e > 30) R[i][j] = LLONG_MAX;
			else {
				ll v = 1;
				loop(q, e){
					if(v < LLONG_MAX/A[i]) v *= A[i];
					else {
						v = LLONG_MAX;
						break;
					}
				}
				R[i][j] = v;
			}
		}
	}

	int Q; scanf("%d",&Q);
	for(int q = 1;q <= Q;q++) {
		int l,r; scanf("%d %d",&l,&r);
		printf("%d\n", solve(l, r, mod));
	}
	return 0;
}
