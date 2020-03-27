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

int a, b, c;
const int MAXA = 10000;
vi divs[MAXA+1];
int prime[MAXA+1];

void sieve(){
	divs[1].pb(1);
	for(int i = 2;i <= MAXA;i++){
		if(!prime[i]){
			prime[i] = i;
			for(ll j = i*(ll)i; j <= MAXA; j += i)
				prime[j] = i;
		}
		int p = prime[i], n = i, e = 0;
		while(n%p == 0){
			e++;
			n /= p;
		}
		for(int q = 1; e >= 0; q *= p, e--)
			for(int d : divs[n])
				divs[i].pb(d * q);
	}
}

int compute(int A, int B, int C){
	return abs(A - a) + abs(B - b) + abs(C - c);
}

void get_C(int A, int B, pair<int, pair<int, pi> > & ans){
	if(B < A) return;
	int C = c - c%B;
	pair<int, pair<int, pi> > tmp;
	if(C >= B){
		tmp.first = compute(A, B, C);
		tmp.second = pair<int, pi> (A, pi(B, C));
		ans = min(ans, tmp);
	}
	C += B;
	tmp.first = compute(A, B, C);
	tmp.second = pair<int, pi> (A, pi(B, C));
	ans = min(ans, tmp);
} 

pair<int, pair<int, pi> > get_targets(int A){
	int B = b - b%A;
	pair<int, pair<int, pi> > ans;
	ans.first = INT_MAX;
	get_C(A, B - A, ans);
	get_C(A, B, ans);
	get_C(A, B + A, ans); 
	return ans;
}

void solve(){
	pair<int, pair<int, pi> > ans;
	ans.first = INT_MAX;
	for(int B = 1; B <= 10000; B++)
		for(int A : divs[B])
			get_C(A, B, ans);
	for(int A = 1; A <= 10000; A++)
		ans = min(ans, get_targets(A));
	printf("%d\n", ans.first);
	printf("%d %d %d\n", ans.second.first, ans.second.second.first, ans.second.second.second);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	sieve();
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d %d", &a, &b, &c);
		solve();
	}
	return 0;
}
