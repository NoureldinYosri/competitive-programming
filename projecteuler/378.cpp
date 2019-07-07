#ifdef DONE
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include "my_math.h"
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

const int MAXN = 60*1000*1000 + 1;
ll dT[MAXN + 1];
int prime[MAXN+1],sig0[MAXN+1];

void compute_dT(ll N) {
	cerr << "sieve" << endl;
	sieve(N+1,prime);
	cerr << "compute sig0" << endl;
	sig0[1] = 1;
	for(int i = 2;i <= N+1;i++) {
		int u = i,p = prime[i],e = 0;
		while(u%p == 0) u /= p,e++;
		sig0[i] = sig0[u]*(e + 1LL);
	}

	cerr << "compute dT" << endl;
	for(int i = 1;i <= N;i++){
		int ctr = 0,a = i,b = i+1;
		while(a%2 == 0) ctr++,a >>= 1;
		while(b%2 == 0) ctr++,b >>= 1;
		assert(ctr);
		dT[i] = sig0[a]*ctr*sig0[b];
	}
}

const ll mod = 1000000000000000000LL;
const int MAXDT = 23040;
ll BIT[2][MAXDT + 1];

ll addLL(ll a,ll b) {
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

void update(int p,ll v,ll *T) {
	for(;p <= MAXDT;p += LSOne(p))
		T[p] = addLL(T[p],v);
}

ll get(int p,ll *T) {
	ll ret = 0;
	for(;p;p ^= LSOne(p))
		ret = addLL(ret,T[p]);
	return ret;
}

int main(int argc,char **argv){
	compute_dT(MAXN-1);
	cerr << "compute answer" << endl;
	ll ans = 0;

	ll N = MAXN-1;
	for(int i = 1;i <= N;i++) {
		int dt = dT[i];
		ll v = addLL(get(MAXDT,BIT[1]),- get(dt,BIT[1]));
		ans = addLL(ans,v);

		v = addLL(get(MAXDT,BIT[0]),- get(dt,BIT[0]));
		update(dt,v,BIT[1]);
		update(dt,1,BIT[0]);
	}
	cout << ans << endl;
	return 0;
}
#endif
