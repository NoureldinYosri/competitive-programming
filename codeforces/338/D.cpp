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


const int MAX = 10000 + 10;
int checked[MAX];
ll n, m;
ll A[MAX];
int K;


bool solve(){
	loop(i, K-1) if(__gcd(A[i], A[i+1]) != 1) return 0;

//	cerr << "check m" << endl;
	ll up = m;
	for (int i = K-1; i >= 0; i--) {
		if (A[i] > up) return false;
		up -= up%A[i];
		up--;
	}

//	cerr << "check n" << endl;
	ll N = 1;
	for (int i = 0; i < K; i++) {
		ll g = __gcd(N, A[i]);
		ll x = A[i]/g;
		if (x > n/N) return false;
		N *= x;
		if (N > n) return false;
	}
	

//	cerr << "check div" << endl;
	int K = ::K+2;
	loop(i, K) checked[i] = ::K;
	
	for (int i = 0; i < ::K; i++)
		for (int j = 2; j < K; j ++)
			if (A[i]%j == 0) {
				if(checked[j] == ::K) {
					if(i - j >= 0) return 0;
					checked[j] = i;
				}
				else if((i - checked[j])%j) {
//					cerr << j << " from " << checked[j] << " to " << i << endl;
					return 0;
				}
			}
	for(int s = 2; s < K; s++)
		for(int p = checked[s]; p < ::K; p += s)
			if(A[p]%s)
				return 0;
	return true;	
	
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%lld %lld %d", &n, &m, &K);
	loop(i, K) scanf("%lld", A + i);
	puts(solve() ? "YES" : "NO");
	return 0;
}
