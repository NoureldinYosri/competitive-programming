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

vector<string> G;
int n;
vector<vi> S;
int dp[55][55][55][55];
bool isEmpty(int x1, int y1, int x2, int y2){
	int ret = S[x2][y2];
	if(x1) ret -= S[x1-1][y2];
	if(y1) ret -= S[x2][y1-1];
	if(x1 && y1) ret += S[x1-1][y1-1];
	return ret == 0; 
}

int solve(int x1, int y1, int x2, int y2){
	if(x1 > x2 || y1 > y2) return 0;
	if(isEmpty(x1, y1, x2, y2)) return 0;
	int & ret = dp[x1][y1][x2][y2];
	if(ret != -1) return ret;
	ret = max(x2-x1, y2-y1) + 1;
	for(int k = x1; k < x2; k++) ret = min(ret, solve(x1, y1, k, y2) + solve(k+1, y1, x2, y2));
	for(int k = y1; k < y2; k++) ret = min(ret, solve(x1, y1, x2, k) + solve(x1, k+1, x2, y2));
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	PRESTDIO();
	cin >> n;
	G.resize(n);
	for(string & s : G) cin >> s;
	
	S.resize(n, vi(n, 0));
	loop(i, n) loop(j, n) {
		S[i][j] = G[i][j] == '#';
		if(i) S[i][j] += S[i-1][j];
		if(j) S[i][j] += S[i][j-1];
		if(i && j) S[i][j] -= S[i-1][j-1];
	}
	
	memset(dp, -1, sizeof dp);
	cout << solve(0, 0, n-1, n-1) << endl;	
	return 0;
}
