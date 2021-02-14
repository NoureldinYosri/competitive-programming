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

const int B = 62, mod = 1e9 + 7;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}
int n;
ll A[1 << 20];
int cnt[B];

int f(int i){
	int ret = 0;
	ll x = A[i];
	loop(b, B){
		int tmp = 0;
		if(x & 1){
			tmp = n;
		} else {
			tmp = cnt[b];
		}
		tmp = mul(tmp, (1LL << b)%mod);
		ret = add(ret, tmp);
		x >>= 1;
	}
	return ret;
}

int g(int i){
	int ret = 0;
	ll x = A[i];
	loop(b, B){
		int tmp = 0;
		if(x & 1){
			tmp = cnt[b];
		}
		tmp = mul(tmp, (1LL << b)%mod);
		ret = add(ret, tmp);
		x >>= 1;
	}
	return ret;	
}

void tc(){
	scanf("%d", &n);
	loop(i, n) scanf("%lld", A + i);
	memset(cnt, 0, sizeof cnt);
	loop(i, n){
		ll x = A[i];
		loop(j, B){
			cnt[j] += x & 1;
			x >>= 1;
		}
	}
	int ans = 0;
	loop(i, n) ans = add(ans, mul(f(i), g(i)));
	printf("%d\n", ans);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
