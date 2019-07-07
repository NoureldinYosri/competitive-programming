#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int mod = 1e9+7;
const int MAXM = 100000 + 10;
int E[MAXM];

int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b){
	return (a*(ll)b)%mod;
}
int EXP(int a,int p) {
	if(p <= 0) return 1;
	int b = 1;
	for(;p > 1; p >>= 1) {
		if(p & 1) b = mul(a,b);
		a = mul(a,a);
	}
	return mul(a,b);
}
int inv(int a) {
	return EXP(a,mod - 2);
}

int prime[MAXM];
vi divs[MAXM];

void sieve(){
	divs[1].push_back(1);
	for(int n = 2;n < MAXM;n++){
		if(!prime[n]) {
			prime[n] = n;
			for(ll j = n*(ll)n;j < MAXM;j += n)
				prime[j] = n;
		}
		int p = prime[n],e = 0,m = n;
		while(m%p == 0) m /= p,e++;
		for(int q = 1;e >= 0;e--) {
			for(int x : divs[m]){
				int y = x*q;
				assert(n%y == 0);
				divs[n].push_back(x*q);
			}
			if(e) q *= p;
		}
	}
}

int cnt[MAXM];

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int m; cin >> m;
	sieve();

	E[1] = 1;
	int im = inv(m),ans = 0;
	for(int i = 2;i <= m;i++) {
		sort(all(divs[i]));
		reverse(all(divs[i]));
		for(int j = 0;j < sz(divs[i]);j++) {
			int g = divs[i][j];
			cnt[g] = m/g;
			for(int k = 0;k < j;k++)
				if(divs[i][k]%g == 0)
					cnt[g] -= cnt[divs[i][k]];
		}
		for(int g : divs[i]) {
			if(g == i) continue;
			E[i] = add(E[i],mul(cnt[g],E[g]));
		}
//		cerr << i << ": ";
//		print(divs[i],int);
//		for(int g : divs[i]) {
//			cerr << "(" << cnt[g] ;
//			int ctr = 0;
//			for(int j = 1;j <= m;j++)
//				if(__gcd(i,j) == g)
//					ctr++;
//			cerr << ", " << ctr << ")";
//		}
//		cerr << endl;
		// e' = 1 + (e + cnt[i]*e') / m
		// (m - cnt[i])/m * e' = 1 + e/m
		int val = add(m,E[i]);
		val = mul(val,inv(m-cnt[i]));
		E[i] = val;
	}
//	prArr(E+1,m,int);
	range(i,1,m) ans = add(ans,E[i]);
	ans = mul(ans,inv(m));
	printf("%d\n",ans);

	return 0;
}
