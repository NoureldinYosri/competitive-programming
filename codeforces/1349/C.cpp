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

const int MAX = 1024;
int m, n, Q;
char grid[MAX][MAX];
int vis_time[MAX][MAX][2];
int G[MAX][MAX];
using state = pair<pi, int>;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};
bool vis[MAX][MAX][2];


deque<state> dq;

void insert(int i, int j, int c, int t){
	if(t < vis_time[i][j][c]){
//		if(!i) cerr << "@" << t << ": " << i << " " << j << " " << c << endl;
		vis_time[i][j][c] = t;
		dq.emplace_back(pi(i, j), c);
	}
}

void bfs(){
	loop(i, m) loop(j, n) loop(r, 4){
		int x = i + dx[r];
		int y = j + dy[r];
		if(x < 0 || y < 0 || x >= m || y >= n) continue;
		if(G[i][j] != G[x][y]) continue;
		int c = G[i][j];
		insert(i, j, c, 0);
		insert(x, y, c, 0);
	}
	
	while(!dq.empty()){
		auto [p, c] = dq.front(); dq.pop_front();
		auto [i, j] = p;
		if(vis[i][j][c]) continue;
		vis[i][j][c] = 1;
		
		int t = vis_time[i][j][c];
		
		insert(i, j, c^1, t + 1);
		
		loop(r, 4){
			int x = i + dx[r];
			int y = j + dy[r];
			if(x < 0 || y < 0 || x >= m || y >= n) continue;
			if(c != G[x][y]) continue;
			if(vis_time[x][y][c] <= t) continue;
			vis_time[x][y][c] = t;
			dq.emplace_front(pi(x, y), c);
		}
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &m, &n, &Q);
	loop(i, m) {
		scanf("%s", grid[i]);
		assert((int)strlen(grid[i]) == n);
		loop(j, n){
			G[i][j] = grid[i][j] - '0';
			vis_time[i][j][0] = vis_time[i][j][1] = INT_MAX;
		}
	}
	bfs();
	while(Q--){
		ll t;
		int i, j;
		scanf("%d %d %lld", &i, &j, &t);
		i--, j--;
		int c = G[i][j];
		if(vis_time[i][j][c] != INT_MAX && vis_time[i][j][c] < t) c ^= (t - vis_time[i][j][c]) & 1;
		printf("%d\n", c);
	}
	return 0;
}
