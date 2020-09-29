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
ll A, R, M;
int H[1 << 20];
ll pref[1 << 20];
ll suff[1 << 20];



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %lld %lld %lld", &n, &A, &R, &M);
	M = min(M, A + R);
	for(int i = 1; i <= n; i++) scanf("%d", H + i);
	sort(H + 1, H + n + 1);
	for(int i = 1; i <= n; i++) pref[i] = pref[i-1] + H[i];
	for(int i = n; i > 0; i--) suff[i] = suff[i+1] + H[i];
	

	ll ans = LLONG_MAX;
	int i = 0;
	for(ll h = H[1]; h <= H[n]; h++){
		while(i+1 <= n && H[i+1] <= h) i++;
		ll E = suff[i+1] - (n - i)*h; 
		ll D = i*h - pref[i];
//		cerr << h << " " << D << " " << E << " " << pref[i] << endl;
		ll d = min(D, E);
		ll tmp = d*M + (E - d)*R + (D - d)*A;
//		cerr << d*M << " " << (E - d)*R << " " << (D-d)*A << " -> " << tmp << endl;
		ans = min(ans, tmp);
	}
	printf("%lld\n", ans);
	
	return 0;
}
