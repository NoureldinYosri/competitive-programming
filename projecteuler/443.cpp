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

ll g[1 << 20];

ll get_k(ll n,ll g) {
	ll k = LLONG_MAX;
	ll u = g - n - 1;
	for(ll i = 1;i*i <= u;i++) {
		if(u%i == 0) {
			ll kd,d;
			if(i > 1) {
				d = i;
				kd = (d - (n+1)%d)%d;
				k = min(k,kd);
			}

			d = u/i;
			kd = (d - (n+1)%d)%d;
			k = min(k,kd);
		}
	}

	assert(k != LLONG_MAX);
	return k;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
//	g[4] = 13;
//	int nxt = 4 + get_k(4,13) + 1;
//	cerr << "@4 predict " << nxt << endl;
//	for(int n = 5;n <= 1000*1000;n++) {
//		int x = __gcd(n+0LL,g[n-1]);
//		g[n] = g[n-1] + x;
//		if(x > 1) {
//			if(n != nxt) {
////				cerr << "found " << n << " predicted " << nxt << endl;
//			}
//			assert(n == nxt);
//			nxt = n + get_k(n,g[n]) + 1;
////			cerr << "@" << n << " " << g[n] << " predict " << nxt << endl;
//		}
//	}
//	assert(g[1000] == 2524);
//	assert(g[1000*1000] == 2624152);

	// gcd(g[n]+k,n+k+1)
	// gcd(n+k+1,g[n]-n-1)
	ll n = 4,g = 13,nxt = n + get_k(n,g) + 1;
	ll target = 1000000000000000LL;
//	target = 1000*1000;
	while(nxt <= target) {
//		cerr << n << " " << g << endl;
		ll k = get_k(n,g);
		n = nxt;
		g += k;
		ll x = __gcd(n,g);
		assert(x > 1);
		g += x;
		nxt = n + get_k(n,g) + 1;
	}
	g += target - n;
	cout << g << endl;
	return 0;
}
#endif
