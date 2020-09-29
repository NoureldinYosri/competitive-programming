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

const int MAX = 55;
char G[MAX][MAX];
int m, n;
int dx [] = {-1, 0, 1, 0};
int dy [] = {0, 1, 0, -1};
bool vis[MAX][MAX];

pi dfs(int i, int j){
	if(vis[i][j] || G[i][j] == '#') return pi(0, 0);
	pi ret;
	ret.first += G[i][j] == 'G';
	ret.second += G[i][j] == 'B';
	vis[i][j] = 1;
	loop(r, 4){
		int x = i + dx[r];
		int y = j + dy[r];
		if(x >= 0 && x < m && y >= 0 && y < n){
			auto [a, b] = dfs(x, y);
			ret.first += a;
			ret.second += b;
		}
	}
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d", &m, &n);
		loop(i, m) scanf("%s", G[i]);
		int target = 0;
		loop(i, m) loop(j, n) {
			target += G[i][j] == 'G';
			vis[i][j] = 0;
		}
		loop(i, m) loop(j, n) if(G[i][j] == 'B'){
			loop(r, 4){
				int x = i + dx[r];
				int y = j + dy[r];
				if(x >= 0 && x < m && y >= 0 && y < n && G[x][y] == '.')
					G[x][y] = '#';
			}
		}
//		loop(i, m) puts(G[i]);
		auto [good, bad] = dfs(m-1, n-1);
		if(good == target && bad == 0)
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}
