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

vector<pair<ll, ll>> W;
int n;

bool can(ll x){
	int small = 0, big = 0, medium = 0;
	ll L = LLONG_MIN, R = LLONG_MAX;
	for(auto [l, r] : W){
		if(r < x) small++, L = max(L, r);
		else if(x < l) big++, R = min(R, l);
		else medium++;
	}
	if(n & 1) {
		return max(small, big) <= n/2;
	}
	else {
		if(max(small, big) > n/2) return 0;
		if(max(small, big) < n/2) return 1;
//		cerr << x << ": " << L << " " << R << endl;
//		cerr << small << " " << medium << " " << big << endl;
		if(min(small, big) == n/2) return (L + R)/2 == x;
		if(big == n/2) return R <= x+1;
		else return x <= L+1;
	}
}

ll BS1(ll s, ll e){
	while(s < e){
		ll m = (s + e) >> 1;
		if(can(m)) e = m;
		else s = m+1;
	}
	return s;
}

ll BS2(ll s, ll e){
	while(s < e){
		ll m = s + (e-s+1)/2;
		if(can(m)) s = m;
		else e = m-1;
	}
	return s;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	W.resize(n);
	for(auto & [a, b] : W) scanf("%lld %lld", &a, &b);
	sort(all(W));
	if(n%2 == 0){
		for(auto & [a, b] : W) a <<= 1, b <<= 1;
	}
	ll mid = W[n/2].first;
	if(n%2 == 0) mid = (W[n/2 - 1].first + W[n/2].first) >> 1;
	
	ll l = BS1(W[0].first, mid);
	ll r = l;
	for(auto p : W) r = max(r, p.second);
	r = BS2(mid, r);
	
//	cerr << l << " " << mid << " " << r << endl;
	
	

	cout << r-l+1 << endl;

	return 0;
}
