#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
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
const double PI = acos(-1);
using namespace std;

const int MAX = 1500 + 10;
char grid[MAX][MAX];
int M,N,Q;
pi A,B;
int dist[4][MAX][MAX];
int dx [] = {0,-1,0,1},dy [] = {-1,0,1,0};

void pad(){
	loop(i,N+2) grid[0][i] = grid[M+1][i] = '$';
	loop(i,M+2) grid[i][0] = grid[i][N+1] = '$';
}

queue<pi> q;

void bfs(int sx,int sy,int dist[MAX][MAX]) {
	if(grid[sx][sy] == '#' || grid[sx][sy] == '$') return;
	q.push(mp(sx,sy));
	dist[sx][sy] = 1;
	while(!q.empty()) {
		int x = q.front().xx,y = q.front().yy; q.pop();
		loop(k,4) {
			int nx = x + dx[k],ny = y + dy[k];
			char c = grid[nx][ny];
			if(c == '$' || c == '#' || c == 'B') continue;
			if(dist[nx][ny]) continue;
			dist[nx][ny] = 1;
			q.push(mp(nx,ny));
		}
	}
//	cerr << sx << " " << sy << endl;
//	range(i,0,M+1) {
//		prArr(dist[i],N+2,int);
//	}
}

int main(){
	freopen("pushabox.in", "r", stdin);
	#ifndef HOME
		freopen("pushabox.out", "w", stdout);
	#endif
	scanf("%d %d %d",&M,&N,&Q);
	range(i,1,M) {
		scanf("%s",grid[i] + 1);
		range(j,1,N){
			if(grid[i][j] == 'A') A = mp(i,j);
			if(grid[i][j] == 'B') B = mp(i,j);
		}
	}
	pad();
//	loop(i,M+2) cerr << grid[i] << endl;
	loop(k,4) bfs(B.xx + dx[k],B.yy + dy[k],dist[k]);

	loop(q,Q) {
		int x,y; scanf("%d %d",&x,&y);
		bool res = 0;
		loop(k,4) {
//			cerr << dist[k][A.xx][A.yy] << " " << dist[(k+2)%4][x][y] << endl;
			if(dist[k][A.xx][A.yy] && dist[(k+2)%4][x][y]) res = 1;
		}
		puts(res ? "YES" : "NO");
	}
	return 0;
}
