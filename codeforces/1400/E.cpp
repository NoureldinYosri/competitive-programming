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

const int MAXN = 5000 + 10;
int A[MAXN], n;
int nxt[MAXN], bigger[MAXN];
map<int, int> lst;
vi H;

int dp[MAXN][MAXN];
int solve(int i, int h){
	assert(i <= n);
	if(i == n) return 0;
	if(A[i] <= h) return 0;
	int & ret = dp[i][h];
	if(ret != -1) return ret;
	ret = 1 + solve(i + 1, h);
	int j = (bigger[i] < n) ? bigger[i] : i;
	int nh = A[j];
	ll tmp = H[nh] - H[h];
	tmp += solve(i, nh);
	for(; j < n; j = nxt[j]){
		tmp += solve(j + 1, nh);
		assert(tmp >= 0);
		tmp = min(tmp, (ll)n);
	}
	ret = min(ret + 0LL, tmp);
	cerr << pi(i, h) << ": " << ret << " " << tmp << endl;
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) {
		scanf("%d", A + i);
		H.pb(A[i]);
	}
	H.pb(0);
	sort(all(H));
	H.resize(unique(all(H)) - H.begin());
	loop(i, n) A[i] = lower_bound(all(H), A[i]) - H.begin();
	vi ST;
	for(int i = n-1; i >= 0; i--){
		nxt[i] = lst[A[i]] ? lst[A[i]] : n;
		lst[A[i]] = i;
		while(!ST.empty() && A[ST.back()] <= A[i]) ST.pop_back();
		bigger[i] = ST.empty() ? n : ST.back();
		ST.pb(i);
	}
	
	memset(dp, -1, sizeof dp);
	cout << solve(0, 0) << endl;

	return 0;
}
