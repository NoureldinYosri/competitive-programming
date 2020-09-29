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


int H, W, n;
char grid[30][30], txt[60];
int dp[30][30][60];
pi choice[30][30][60];

int solve(int x, int y, int i){
	if(x < 0 || x >= H || y < 0 || y >= W) return -1e9;
	if(i == n-1) return txt[i] == grid[x][y];
	int & ret = dp[x][y][i];
	if(ret != -1) return ret;
	ret = 0;
	for(int dx = -1; dx <= 1; dx++)
		for(int dy = -1; dy <= 1; dy++)
			if(dx || dy){
				int tmp = solve(x + dx, y + dy, i + 1);
				if(tmp >= ret){
					ret = tmp;
					choice[x][y][i] = pi(dx, dy);
				}
			}
	ret += txt[i] == grid[x][y];
	return ret;
}

int main(){
	freopen("kingwalk.in", "r", stdin);
	freopen("kingwalk.out", "w", stdout);
	scanf("%d %d", &H, &W);
	loop(i, H) scanf("%s", grid[i]);
	scanf("%d %s", &n, txt);
	memset(dp, -1, sizeof dp);
	pair<int, pi> ans(-1, pi(0, 0));
	loop(i, H) loop(j, W) ans = max(ans, mp(solve(i, j, 0), pi(i, j)));
	auto [x, y] = ans.second;
	printf("%d\n", ans.first);
	loop(i, n){
		printf("%d %d\n", x + 1, y + 1);
		auto [dx, dy] = choice[x][y][i];
		x += dx;
		y += dy;
	}
	return 0;
}
