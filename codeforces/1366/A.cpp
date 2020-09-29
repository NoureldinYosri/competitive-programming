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

const int MAX = 10*1000*1000 + 10;
int f[MAX], g[MAX];
int prime[MAX];
list<int> divs[MAX];

void seive(){
	divs[1].pb(1);
	for(int i = 2; i < MAX; i++){
		if(!prime[i]){
			prime[i] = i;
			for(ll j = i*(ll)i; j < MAX; j += i)
				prime[j] = i;
		}
		int p = prime[i];
		int n = i, e = 0;
		while(n%p == 0){ 
			n /= p;
			e++;
		}
		for(ll q = 1; e >= 0; q *= p, e--)
			for(int x : divs[n])
				divs[i].pb(x*q);
	}
	for(int n = 1; n < MAX; n++){
		f[n] = g[n] = -1;
		for(int a : divs[n]){
			for(int b : divs[n/__gcd(n, a)])
				if(__gcd(a + b, n) == 1){
					f[n] = a;
					g[n] = b;
					break;
				}
			if(f[n] != -1) break;
		}
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	seive();
	return 0;
}
