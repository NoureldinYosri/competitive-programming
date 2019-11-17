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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;


int n;
ll B[1 << 20];
int len[1 << 20];
int nxt[1 << 20];
int dont[1 << 20];

bool cond(ll y,ll x) {
	ll g = __gcd(x,y);
	y /= g;
	x /= g;
	return y%2 && x%2;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	map<ll,vector<ll>> M;
	loop(i,n) {
		scanf("%lld",B + i);
		ll x = B[i];
		int k = 0;
		while(x%2 == 0) {
			x >>= 1;
			k++;
		}
		M[k].push_back(B[i]);
	}
	vector<ll> ans;
	for(auto p : M)
		if(sz(p.second) > sz(ans))
			ans = p.second;
	set<ll> S{B,B + n};
	for(ll x : ans) S.erase(x);
	printf("%d\n",sz(S));
	for(ll x : S) printf("%lld ",x);
	return 0;
}
