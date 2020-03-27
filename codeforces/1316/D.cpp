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

const int MAX = 1 << 10;
char G[MAX][MAX];
pi E[MAX][MAX];
int n;
int vis[MAX][MAX];
queue<pi> q;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
char dir[] = "URDL";
bool done[MAX][MAX];


bool dfs(int x, int y){
	if(vis[x][y] == 1) return 0;
	if(vis[x][y]) return 1;
	vis[x][y] = 2;
	
	loop(r, 4){
		int nx = x + dx[r];
		int ny = y + dy[r];
		if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
		if(E[nx][ny].first >= 0) continue;
		
		if(dfs(nx, ny)){
			G[x][y] = dir[r];
			q.emplace(x, y);
			vis[x][y] = 1;
			done[x][y] = 1;
			return 1;
		}
	}
	
	vis[x][y] = 1;
	return 0;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n){
		loop(j, n) {
			scanf("%d %d", &E[i][j].first, &E[i][j].second);
			E[i][j].first--;
			E[i][j].second--;
			G[i][j] = '$';
		}
	}
	loop(i, n) loop(j, n) if(E[i][j] == pi(i, j)) {
		q.emplace(i, j);
		vis[i][j] = 1;
		G[i][j] = 'X';
	}
	
	while(!q.empty()){
		pi p = q.front(); q.pop();
		int x = p.first, y = p.second;
		loop(r, 4){
			int nx = x + dx[r];
			int ny = y + dy[r];
			if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if(vis[nx][ny]) continue;
			if(E[nx][ny] != E[x][y]) continue;
			vis[nx][ny] = 1;
			G[nx][ny] = dir[(r + 2)%4];
			q.emplace(nx, ny);
		}
	}
	
	loop(i, n) loop(j, n) if(!vis[i][j] && E[i][j].first >= 0){
		puts("INVALID");
		return 0;
	}
	
	loop(i, n) loop(j, n) if(!vis[i][j] && E[i][j].first < 0){
		dfs(i, j);
	}
	
	while(!q.empty()){
		pi p = q.front(); q.pop();
		int x = p.first, y = p.second;
		loop(r, 4){
			int nx = x + dx[r];
			int ny = y + dy[r];
			if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if(done[nx][ny]) continue;
			if(E[nx][ny] != E[x][y]) continue;
			done[nx][ny] = 1;
			G[nx][ny] = dir[(r + 2)%4];
			q.emplace(nx, ny);
		}		
	}

	loop(i, n) loop(j, n) if(E[i][j].first < 0 && !done[i][j]) {
		puts("INVALID");
		return 0;		
	}
	
	puts("VALID");
	loop(i, n) puts(G[i]);
	
	return 0;
}
