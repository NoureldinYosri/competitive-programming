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


const int W = 3;
ll A[1 << 20];
int n;
ll S[1 << 20];
unordered_set<ll> used;

vector<ll> get_divs(ll x){
	vector<ll> ret;
	for(ll d = 2;d*d <= x; d++){
		if(x%d) continue;
		if(!used.count(d)) ret.pb(d);
		used.insert(d);
		while(x%d == 0) x /= d;
	}
	if(x > 1 && !used.count(x)) ret.pb(x), used.insert(x);
	return ret;
}


ll B[1 << 20];
int f[1 << 20];
int m;

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%lld", A + i);
	ll g = 0;
	int ans = 0;
	loop(i, n) g = __gcd(g, A[i]), ans += A[i]&1;
	if(g > 1) {
		puts("0");
		return 0;
	}
	sort(A, A + n);
	for(int i = 0;i < n; ){
		int j = i;
		while(j < n && A[i] == A[j]) j++;
		B[m] = A[i];
		f[m] = j-i;
		m++;
		i = j;
	}

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

	vi ord(m);
	loop(i, m) ord[i] = i;
	shuffle(ord.begin(), ord.end(), rng);


	loop(r, min(m, 30)){
		ll v0 = B[ord[r]];
		for(ll v = max(2LL, v0 - W); v <= v0 + W; v++) {
			for(ll g : get_divs(v)){
				ll tmp = 0;
				loop(i, m) {
					ll r = B[i]%g;
					ll v = g - r;
					if(A[i] - r > 0) v = min(v, r);
					tmp += f[i]*v;
					if(tmp > ans) break;
				}		
				if(tmp < ans) ans = tmp;			
			}
		}
	}
	cout << ans << endl;
	return 0;
}
