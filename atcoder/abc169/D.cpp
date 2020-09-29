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

int dp[100][100];

int f(int e, int low){
	if(e == 0) return e;
	int & ret = dp[e][low];
	if(ret != -1) return ret;
	ret = 0;
	for(int x = low; x <= e; x++)
		ret = max(ret, 1 + f(e - x, low + 1));
	return ret;	
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int ans = 0;
	memset(dp, -1, sizeof dp);
	ll n; cin >> n;
	for(ll x = 2; x*x <= n; x++){
		int e = 0;
		while(n%x == 0) {
			e++;
			n /= x;
		}
		ans += f(e, 1);
	}
	if(n > 1) ans += f(1, 1);
	cout << ans << endl;
	return 0;
}
