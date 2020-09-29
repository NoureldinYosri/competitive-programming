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


const int MAX = 200*1000 + 10;
int prime[MAX];

void sieve(){
	for(int i = 2;  i < MAX; i++)
		if(!prime[i]){
			prime[i] = i;
			for(ll j = i*(ll)i; j < MAX; j += i)
				prime[j] = i;
		}
}

vi E[MAX];

void factor(int x){
	while(x > 1){
		int e = 0, p = prime[x];
		while(x%p == 0){
			x /= p;
			e++;
		}
		E[p].pb(e);
	}
}

ll get_power(ll x, int p){
	ll y = 1;
	loop(i, p) y *= x;
	return y;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	sieve();
	int n; scanf("%d", &n);
	loop(i, n) {
		int x; scanf("%d", &x);
		factor(x);
	}
	ll ans = 1;
	for(int p = 2; p < MAX; p++) if(prime[p] == p && !E[p].empty()){
		vi & V = E[p];
		int mn = INT_MAX, second_mn = INT_MAX;
		for(int x : V){
			second_mn = min(second_mn, x);
			if(second_mn < mn) swap(mn, second_mn);
		}
		if(sz(V) == n) ans *= get_power(p, second_mn);
		else if(sz(V) == n-1) ans *= get_power(p, mn);
	}
	cout << ans << endl;
	return 0;
}
