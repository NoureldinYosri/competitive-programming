#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
using namespace std;

const int MAX = 25;
char G[MAX][MAX];
int R,C;
int vis[MAX][MAX];
int id[MAX][MAX],siz[MAX*MAX];

int dfs(int r,int c,int id) {
	if(vis[r][c]) return 0;
	::id[r][c] = id;
	vis[r][c] = 1;
	int ret = 1;
	if(r+1 < R && G[r][c] == G[r+1][c])
		ret += dfs(r+1,c,id);
	if(c+1 < C && G[r][c] == G[r][c+1])
		ret += dfs(r,c+1,id);
	return ret;
}


queue<pi> q;
int dx [] = {0,-1,0,1},dy[] = {-1,0,1,0};

int bfs(int r,int c,int sx,int ex,int sy,int ey) {
	if(r < 0 || r >= R || c < 0 || c >= C) return 0;
	memset(vis,0,sizeof vis);
	q.push(mp(r,c));
	vis[r][c] = 1;
	int ret = 0;
	while(!q.empty()) {
		pi cur = q.front(); q.pop();
		ret++;
		loop(i,4) {
			int nx = cur.xx + dx[i],ny = cur.yy + dy[i];
			if(nx < sx || nx > ex || ny < sy || ny > ey) continue;
			if(vis[nx][ny] || G[nx][ny] != G[r][c]) continue;
			vis[nx][ny] = 1;
			q.push(mp(nx,ny));
		}
	}

	return ret;
}

int getlu(int r,int c) {
	return bfs(r,c,0,r,0,c);
}
int getru(int r,int c) {
	return bfs(r,c,0,r,c,C-1);
}
int getleft(int r,int c) {
	return bfs(r,c,r,R-1,0,c);
}
int getright(int r,int c) {
	return bfs(r,c,r,R-1,c,C-1);
}


int solve(){
	int ret = 0,ctr = 0;
	memset(vis,0,sizeof vis);
	loop(i,R) loop(j,C) if(!vis[i][j]) {
		siz[ctr] = dfs(i,j,ctr);
		ret = max(ret,siz[ctr]);
		ctr++;
	}
	loop(r,R) loop(c,C) {
		int tmp = getleft(r,c-1) + getright(r,c) + getlu(r-1,c-1) + getru(r-1,c);
		ret = max(ret,tmp);
	}

	return ret;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	range(t,1,T) {
		scanf("%d %d",&R,&C);
		loop(i,R) scanf("%s",G[i]);
		printf("Case #%d: %d\n",t,solve());
	}
	return 0;
}
