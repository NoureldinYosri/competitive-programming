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

const int MAX = 1 << 20;
int prime[MAX];

void sieve(){
	for(int i = 2; i < MAX; i++)
		if(prime[i] == 0){
			prime[i] = i;
			for(ll j = i*(ll)i; j < MAX; j += i)
				prime[j] = i;
		}
}


int getCore(int x){
	int y = 1;
	while(x > 1){
		int p = prime[x], e = 0;
		while(x%p == 0){
			x /= p;
			e ^= 1;
		}
		if(e) y *= p;
	}
	return y;
}

void tc(){
	map<int, int> M;
	int n; scanf("%d", &n);
	loop(i, n){
		int x; scanf("%d", &x);
		M[getCore(x)]++;
	}
	int ans[2] = {0, 0};
	int tmp = n;
	for(auto [x, s] : M){
		ans[0] = max(ans[0], s);
		if(s & 1) {
			if(x > 1) tmp -= s;
			ans[1] = max(ans[1], s);
		}
	}
	ans[1] = max(ans[1], tmp);
	ans[1] = max(ans[1], 1);
	int m; scanf("%d", &m);
	while(m--){
		ll w; scanf("%lld", &w);
		w = w > 0;
		printf("%d\n", ans[w]);
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	sieve();
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
