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


int n;
vi A;
ll dp[1 << 20][2][4];

ll solve(int i, int can_take, int k){
	if(i < k) return 0;
	if(i == 0) return A[0];
	ll & ret = dp[i][can_take][k];
	if(ret != -1) return ret;
	ret = A[i] + solve(i-2, can_take, k);
	if(can_take && i-1 >= k) ret = max(ret, A[i] + A[i-1] + solve(i-3, 0, k));
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	PRESTDIO();
	cin >> n;
	A.resize(n);
	for(int & x : A) cin >> x;
	
	if(n == 1){
		cout << A[0] << endl;
		return 0;
	}

	memset(dp, -1, sizeof dp);
	ll ans = 0;
	loop(i, n-1) ans = max(ans, solve(i, 1, 0));
	
	ans = max(ans, solve(n-1, 1, 1));
	ans = max(ans, solve(n-1, 0, 2) + A[0]);

	cout << ans << endl;
	return 0;
}
