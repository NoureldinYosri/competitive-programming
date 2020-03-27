#pragma GCC optimize ("O3")
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
using namespace std;


vector<ll> V;

void inc(ll p2){
	int rem = 2;
	loop(i, sz(V)) {
		if(V[i] & p2) continue;
		V[i] |= p2;
		rem--;
		if(!rem) return;
	}
	for(;rem;rem--) V.pb(p2);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	ll u, v;
	cin >> u >> v;
	if(v == 0){
		if(u == 0) puts("0");
		else puts("-1");
		return 0;
	}
	V.pb(0);
	ll p2 = 1;
	for(;u || (v > 0); u>>=1, v>>=1, p2 <<= 1){
		int bu = u & 1;
		int bv = v & 1;
		if(bu && bv){
			V[0] |= p2;
			v --;
		}
		else if(bu){
			if(p2 == 1){
				puts("-1");
				return 0;
			}
			inc(p2 >> 1);
			V[0] |= p2;
			v -= 2;
		}
		else if(bv){
			if(p2 == 1) {
				puts("-1");
				return 0;
			}
			inc(p2 >> 1);
			v --;
		}
//		print(V, ll);
//		cerr << v << endl;
	}
	if(v < 0) {
		puts("-1");
		return 0;
	}
	printf("%d\n", sz(V));
	for(ll x : V) printf("%lld ", x);
	puts("");
	return 0;
}
