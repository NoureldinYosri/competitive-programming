#ifdef DEBUG
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

#define mul(a,b) (((a)*1LL*(b))%P)
const int MAX = 1000*1000 + 10;
int A[MAX],B[MAX],N,Q,P,M;
int inv[MAX];
vi C[MAX];

int prime[MAX];
vi primes;
int POW[15][MAX*35];
vp f;

void sieve(){
	for(int i = 2;i < MAX;i++)
		if(!prime[i]) {
			prime[i] = i;
			for(ll j = i*1LL*i;j < MAX;j += i)
				prime[j] = i;
		}
}


int powmod(int a,int p){
	if(!p || a == 1) return 1%P;
	int b = 1;
	for(;p > 1; p >>= 1) {
		if(p & 1) b = mul(a,b);
		a = mul(a,a);
	}
	return mul(a,b);
}

vp factorize(int g) {
	vp ret;
	for(int p : primes){
		if((p*1LL*p) > g) break;
		if(g%p == 0) {
			int e = 0;
			while(g%p == 0) g /= p,e++;
			ret.pb(mp(p,e));
		}
	}
	if(g > 1) ret.pb(mp(g,1));
	return ret;
}

void preprocess(){
	f = factorize(P);
	int phi = P;
	for(auto q : f){
		int p = q.xx;
		phi -= phi/p;
	}
	loop(i,N) {
		int g = __gcd(A[i],P);
		A[i] /= g;
		C[i] = vi(sz(f),0);
		for(int j = 0;j < sz(f);j++) {
			int p = f[j].xx;
			while(g%p == 0) C[i][j]++,g /= p;
		}
		assert(g == 1);
		if(i){
			A[i] = mul(A[i],A[i-1]);
			for(int j = 0;j < sz(f);j++)
				C[i][j] += C[i-1][j];
		}
		inv[i] = powmod(A[i],phi-1);
	}
	for(int i = 0;i < sz(f);i++) {
		int mx = C[N-1][i],p = f[i].xx;
		POW[i][0] = 1;
		for(int j = 1;j <= mx;j++)
			POW[i][j] = mul(POW[i][j-1],p);
	}
}



int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	sieve();
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%d %d %d",&N,&P,&Q);
		M = Q/64 + 2;
		loop(i,N) scanf("%d",A + i);
		loop(i,M) {
			scanf("%d",B + i);
			B[i] = (B[i]%N + N)%N;
		}
		preprocess();
		int x = 0,l,r;
		loop(i,Q) {
			cerr << "x = " << x << endl;
			if(i%64 == 0) {
				l = (B[i/64] + x)%N;
				r = (B[i/64 + 1] + x)%N;
			}
			else {
				l = (l + x)%N;
				r = (r + x)%N;
			}
			if(l > r) swap(l,r);
			cerr << l << " " << r << endl;
			int ret = A[r];
			vi E = C[r];
			if(l) {
				ret = mul(ret,inv[l-1]);
				for(int i = 0;i < sz(E);i++)
					E[i] -= C[l-1][i];
			}
			for(int i = 0;i < sz(E);i++)
				ret = mul(ret,POW[i][E[i]]);
			cerr << "res = " << ret << endl;
			x = (ret + 1)%P;
		}
		printf("%d\n",x);
		cerr << "==============================" << endl;
	}
	return 0;
}
#endif
