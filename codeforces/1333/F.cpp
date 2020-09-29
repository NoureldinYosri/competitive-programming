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


const int MAXA = 500*1000 + 10;

int prime[MAXA], f[MAXA];

void sieve(){
	for(int i = 2; i < MAXA; i++)
		if(!prime[i]){
			prime[i] = i;
			for(ll j = i*(ll)i; j < MAXA; j += i)
				prime[j] = i;
		}
	f[1] = 1;
	for(int i = 2; i < MAXA; i++){
		int n = i;
		while(n > 1){
			int p = prime[n];
			f[i] = max(f[i], i / p);
			while(n%p == 0) n /= p;
		}
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	sieve();
	int n; scanf("%d", &n);
	vi A(n);
	loop(i, n) A[i] = i+1;
	sort(all(A), [](const int & a, const int &b){
		return f[a] < f[b];
	});
	for(int i = 2; i <= n;i++)
		printf("%d%c", f[A[i-1]], " \n"[i==n]);
	return 0;
}
