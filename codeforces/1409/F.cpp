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

const int MAXN = 202;
int n, K;
ll dp[MAXN][MAXN][MAXN];
string txt, patt;


ll solve(int i, int k, int open){
	assert(k >= 0);
	if(i == n) return 0;
	ll & ret = dp[i][k][open];
	if(ret != -1) return ret;
	ret = solve(i + 1, k, open);
	char c = txt[i];
	for(char tc : patt){
		if(k - (c != tc) < 0) continue;
		ret = max(ret, open * (tc == patt[1]) + solve(i + 1, k - (c != tc), open + (tc == patt[0])));
	}
	
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> n >> K >> txt >> patt;
	memset(dp, -1, sizeof dp);
	cout << solve(0, K, 0) << endl;
	return 0;
}
