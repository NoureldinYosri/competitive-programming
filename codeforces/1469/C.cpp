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

int n;
ll k;
ll H[1 << 20];
ll L[1 << 20], R[1 << 20];

pair<ll, ll> f(int i, int j){
	ll l = H[j] - H[i] - (k - 1);
	ll r = H[j] - H[i] + (k - 1);
	return mp(l, r);
}



void tc(){
	scanf("%d %lld", &n, &k);
	loop(i, n) scanf("%lld", H + i);
		
	ll low = 0, high = 0;
	L[0] = 0;
	R[0] = 0;
	for(int i = 1; i < n; i++) {
		auto [l, r] = f(i, i - 1);
		low += l;
		high += r;
		low = max(low, 0LL);
		high = min(high, k - 1);
		L[i] = low;
		R[i] = high;
	}
	low = high = 0;
	for(int i = n-2; i >= 0; i--){
		auto [l, r] = f(i, i + 1);
		low += l;
		high += r;
		low = max(low, 0LL);
		high = min(high, k - 1);
		L[i] = max(L[i], low);
		R[i] = min(R[i], high);		
	}
	loop(i, n){
		if(L[i] > R[i]){
			puts("NO");
			return;
		}
	}
	if(L[0] > 0 || L[n-1] > 0){
		puts("NO");
		return;
	}
	puts("YES");
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
