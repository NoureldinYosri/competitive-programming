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

map<ll, int> lg;
int f[] = {0, 2, 3, 1};

ll solve(ll n){
	if(n <= 3) return n;
	n -= 1;
	ll row = n/3 + 1;
	ll col = n%3;
	
	ll p2 = 1, cnt = 1, cnt0 = 0;
	while(cnt < row){
		p2 *= 4;
		cnt0 = cnt;
		cnt += p2;
	}
	
	ll a = row - cnt0 - 1;
//	cerr << row << " " << cnt0 << " " << p2 << endl;
	a |= p2;
	
	if(col == 0) return a;
	
	p2 <<= 1;
	ll b = p2;
	p2 >>= 2;
	
	int k = lg[p2] + 1;
	row = row - cnt0 - 1;
	assert(k%2 == 0);
	for(;k; k -= 2){
		ll c = 1LL << (k-2);
		ll x = row/c;
		x = f[x];
		b |= x << (k-2);
		row %= c;
	}
	if(col == 1) return b;
//	cerr << a << " " << b << " " << (a^b) << endl;
	return a^b;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	for(int i = 0; i <= 62; i++)
		lg[1LL << i] = i;
		
	int T; scanf("%d", &T);
	while(T--){
		ll n;
		scanf("%lld", &n);
		printf("%lld\n", solve(n));
	}

	return 0;
}
