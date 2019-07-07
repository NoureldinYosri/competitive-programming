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
const int MAX = 1000*1000 + 10,MAXNUM = 10;
int A[MAX],B[MAX],N,Q,P,M;
int inv[MAX];
int C[MAX][MAXNUM];

int prime[MAX];
vi primes;
int POW[MAXNUM][MAX*40];
vp f;

void sieve(){
	for(int i = 2;i < MAX;i++)
		if(!prime[i]) {
			prime[i] = i;
			primes.push_back(i);
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

	A[0] = 1;
	inv[0] = 1;
	range(i,1,N) {
		for(int j = 0,p;j < sz(f);j++) {
			p = f[j].xx;
			C[i][j] = 0;
			while(A[i]%p == 0){
				C[i][j]++;
				A[i] /= p;
			}
			C[i][j] += C[i-1][j];
		}

		A[i] = mul(A[i],A[i - 1]);
		inv[i] = powmod(A[i],phi-1);
	}
	for(int i = 0;i < sz(f);i++) {
		int mx = C[N][i],p = f[i].xx;
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
		M = (Q >> 6) + 2;
		range(i,1,N) scanf("%d",A + i);
		loop(i,M) {
			scanf("%d",B + i);
			B[i] = (B[i]%N + N)%N;
		}
		preprocess();

		int x = 0,l,r,z;
		loop(i,Q) {
			x %= N;
			if(i%64 == 0) {
				l = B[i >> 6] + x;
				r = B[(i >> 6) + 1] + x;
			}
			else {
				l += x;
				r += x;
			}
			if(l >= N) l -= N;
			if(r >= N) r -= N;
			if(l > r) swap(l,r);

			x = mul(A[r + 1],inv[l]);
			z = 1;
			for(int k = 0;k < sz(f);k++) {
				int e = f[k].yy;
				int pe = C[r+1][k] - C[l][k];
				z &= pe >= e;
				x = mul(x,POW[k][pe]);
			}
//			cerr << l << " " << r << " -> " << x << " " << z << endl;
			x = z ? 0 : x;
			x++;
			if(x >= P) x = 0;
		}
		printf("%d\n",x);
//		cerr << "=========================" << endl;
	}
	return 0;
}
