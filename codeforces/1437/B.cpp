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

map<vector<vi>, int> dp[20][20];

int solve(int i, int j, vector<vi> g){
	int n = sz(g), m = sz(g[0]);
	if(j == m) return solve(i + 1, 0, g);
	if(i == n) return 0;
	if(dp[i][j].count(g)) return dp[i][j][g];
	int ret = solve(i, j + 1, g);
	if(g[i][j] == 0){
		g[i][j] = 1;
		int n = sz(g);
		for(int r = i; r < n; r++)
			for(int c = (j + 1)*(r == i); c < m; c++)
				if(g[r][c] == 0 && abs(i - r) + abs(j - c) == 3){
					g[r][c] = 1;
					ret = max(ret, 1 + solve(i, j + 1, g));
					g[r][c] = 0;
				}
		g[i][j] = 0;
	}
	dp[i][j][g] = ret;
	return ret;
}

int f(int n, int m){
	vector<vi> g(n, vi(m, 0));
	return solve(0, 0, g);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	for(int n = 1; n <= 20; n++){
		for(int m = 1; n*m <= 20;m ++) {
			cout << f(n, m) << " ";
			fflush(stdout);
		}
		cout << endl;
	}
	return 0;
}
