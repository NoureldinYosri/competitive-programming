#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 60;
int L[MAX],R[MAX],U[MAX],D[MAX],m,n;
char G[MAX][MAX];
int vis[MAX][MAX];
bool vis2[MAX][MAX][4][2];
bool dp[MAX][MAX][4][2][2];
int dx[] = {-1,0,1,0},dy[] = {0,-1,0,1};
int Tx,Ty;

void dfs(int x,int y){
	if(x < 0 || y < 0 || x == m || y == n || vis[x][y] || G[x][y] != 'B') return;
	vis[x][y] = 1;
	dfs(x-1,y);
	dfs(x+1,y);
	dfs(x,y-1);
	dfs(x,y+1);
}

int bfs(){
	memset(vis,0,sizeof vis);
	memset(vis2,0,sizeof vis2);
	queue<pair<pi,pi> > q;
	loop(i,4) vis2[Tx][Ty][i][1] = 1,q.push(mp(mp(Tx,Ty),mp(i,1)));
	while(!q.empty()){
		int x = q.front().xx.xx,y = q.front().xx.yy,dir = q.front().yy.xx,k = q.front().yy.yy; q.pop();
		vis[x][y] = 1;
		int nx = x + dx[dir],ny = y + dy[dir];
		if(0 <= nx && nx < m && 0 <= ny && ny < n && !vis2[nx][ny][dir][k] && G[nx][ny] == 'B') {
			q.push(mp(mp(nx,ny),mp(dir,k)));
			vis2[nx][ny][dir][k] = 1;
		}
		if(k){
			for(dir = 0;dir < 4;dir++){
				nx = x + dx[dir],ny = y + dy[dir];
				if(0 <= nx && nx < m && 0 <= ny && ny < n && !vis2[nx][ny][dir][0] && G[nx][ny] == 'B') {
					q.push(mp(mp(nx,ny),mp(dir,0)));
					vis2[nx][ny][dir][0] = 1;
				}
			}
		}
	}
	//loop(i,m) {prArr(vis[i],n,int);}
}

int main(){
	scanf("%d %d",&m,&n);
	loop(i,m) scanf("%s",G[i]);
	int u = -1,v = -1;
	loop(i,m) loop(j,n) if(G[i][j] == 'B') u = i,v = j;
	dfs(u,v);	
	loop(i,m) loop(j,n) if(G[i][j] == 'B' && !vis[i][j]){
		puts("NO");
		return 0;
	}	
	for(Tx = 0;Tx < m;Tx++)
		for(Ty = 0;Ty < n;Ty++)
			if(G[Tx][Ty] == 'B'){
				bfs();
				loop(i,m) loop(j,n) if(G[i][j] == 'B' && !vis[i][j]){
					//cerr << i << " " << j << " can't " << Tx << " " << Ty << endl;
					puts("NO");
					return 0;
				}
			}
	puts("YES");
	return 0;
}
