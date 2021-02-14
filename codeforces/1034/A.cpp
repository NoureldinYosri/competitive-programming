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

const int MAX = 1.5e7 + 10;
int prime[MAX];

void sieve(){
	for(int i = 2; i < MAX; i++)
		if(prime[i] == 0){
			prime[i] = i;
			for(ll j = i*(ll)i; j < MAX; j += i)
				prime[j] = i;
		}
}

int f[MAX], n;
int g[MAX];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	sieve();
	scanf("%d", &n);
	vi A(n);
	int g = 0;
	for(int & a : A){
		scanf("%d", &a);
		g = gcd(g, a);
	}
	vi P;
	for(int a : A) {
		a /= g;
		while(a > 1){
			int p = prime[a];
			f[p]++;
			while(a%p == 0) a /= p;
		}
	}
	
	f[1] = 0;
	int ans = n - *max_element(f, f + MAX);
	if(ans == n) ans = -1;
	cout << ans << endl;
	
	return 0;
}
