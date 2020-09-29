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

const int mod = 1000000007;

int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}

int powmod(int x, int p){
	if(p <= 0) return 1;
	int y = 1;
	for(; p > 1; p >>= 1) {
		if(p & 1) y = mul(x, y);
		x = mul(x, x);
	}
	return mul(x, y);
}


int n, p;
int A[1 << 20];

void canonize(vp & V){
	static vp aux;
	aux.clear();
	for(auto [k, a] : V){
		if(aux.empty() || aux.back().first != k) {
			aux.emplace_back(k, a);
		}
		else {
			aux.back().second += a;
		}
	}
	V.clear();
	int lst = -1, e = 0;
//	cerr << "second loop" << endl;
	for(auto [k, a] : aux){
//		cerr << k << " " << a << "\t" << lst << " " << e << endl;
		while(lst < k && e >= p){
			if(e%p == 0) V.emplace_back(lst, e%p);
			e /= p;
			lst++;
		}
//		cerr << "continue" << endl;
		if(lst != k){
			if(e) V.emplace_back(lst, e);
			lst = k;
			e = 0;
		}
		e += a;
		if(e%p) V.emplace_back(k, e%p);
		e /= p;
		lst = k + 1;
	}
//	cerr << "last loop" << endl;
//	cerr << lst << " " << e << endl;
	while(e) {
		if(e%p == 0) V.emplace_back(lst, e%p);
		e /= p;
		lst++;
	}
//	cerr << "return" << endl;
}

void get(int s, int e, int z, vp & V){
	V.clear();
	for(int i = s; i <= e; i++){
		V.emplace_back(A[i], 1);
	}
	if(z != -1) V.emplace_back(z, 1);
//	for(auto p : V) cerr << p ;
//	cerr << endl;
//	cerr << "canonize" << endl;
	canonize(V);
//	cerr << "return" << endl;
}


bool cmp(int k, int mx){
	static vp U, V;
	get(0, k-1, mx, U);
	get(k, n-1, -1, V);
//	for(auto p : U) cerr << p;
//	cerr << endl;
//	for(auto p : V) cerr << p;
//	cerr << endl;
	
	while(!V.empty() && !U.empty() && U.back() == V.back()) {
		U.pop_back();
		V.pop_back();
	}
	if(!U.empty() && !V.empty()) {
		auto [ka, va] = U.back();
		auto [kb, vb] = V.back();
		if(ka != kb) return kb > ka;
		return vb > va;
	}
	return U.empty();
}

int f(int k, int mx){
	static vp U, V;
	get(0, k-1, mx, U);
	get(k, n-1, -1, V);
	
	int diff = 0;
	for(auto [k, e] : V){
//		cerr << e << " * " << p << "^" << k << endl;
		diff = add(diff, mul(e, powmod(p, k)));
	}
//	cerr << endl;
	for(auto [k, e] : U){
//		cerr << e << " * " << p << "^" << k << endl;
		diff = add(diff, -mul(e, powmod(p, k)));
	}
//	cerr << endl;
	
	if(!cmp(k, mx)) diff = add(0, -diff);
	return diff;
}

int solve(){
	if(p == 1) return n & 1;
	sort(A, A + n);
	int mx = -1;
	
	while(mx == -1 && n){
		int cnt = 0;
		mx = A[n-1];
		while(n && A[n-1] == mx) {
			n--;
			cnt++;
		}
		if(cnt & 1) break;
		mx = -1;
	}
	if(n == 0) return (mx == -1) ? 0 : powmod(p, mx);
	assert(mx != -1);
	assert(A[n-1] < mx);
	
	int s = 0, e = n;
	while(s < e){
		int m = s + (e-s+1)/2;
		if(cmp(m, mx)) s = m;
		else e = m-1;
	}
	
//	cerr << s << " " << n << " " << cmp(s, mx) << endl;

	return f(s, mx);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d", &n, &p);
		loop(i, n) scanf("%d", A + i);
		printf("%d\n", solve());
	}
	return 0;
}
