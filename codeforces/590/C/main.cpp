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

const int oo = 1 << 29;
char G[1000][1001];
int m,n;
int dist[3][1000][1001];
int dx[] = {0,-1,0,1},dy[] = {-1,0,1,0};

void bfs(char a,int dist[1000][1001]){
	loop(i,m) loop(j,n) dist[i][j] = oo;
	queue<pi> q;
	loop(i,m) loop(j,n) if(G[i][j] == a) q.push({i,j}),dist[i][j] = 0;
	int ret = oo;
	while(!q.empty()){
		int x = q.front().xx,y = q.front().yy; q.pop();
		loop(i,4){
			int nx = x + dx[i],ny = y + dy[i];
			if(nx < 0 || nx >= m || ny < 0 || ny >= n || dist[nx][ny] != oo || G[nx][ny] == '#') continue;
			dist[nx][ny] = dist[x][y] + 1;
			q.push({nx,ny});
		}
	}
}

int main(){
	scanf("%d %d",&m,&n);
	loop(i,m) scanf("%s",G[i]);
	bfs('1',dist[0]);
	bfs('2',dist[1]);
	bfs('3',dist[2]);
	int ans = oo;
	loop(i,m) loop(j,n) ans = min(ans,dist[0][i][j] + dist[1][i][j] + dist[2][i][j] - 2);
	cerr << dist[0][1][1] << " " << dist[1][1][1] << " " << dist[2][1][1] << endl;
	int ab = oo,bc = oo,ac = oo;
	loop(i,m) loop(j,n) if(G[i][j] == '2') ab = min(ab,dist[0][i][j] - 1);
	loop(i,m) loop(j,n) if(G[i][j] == '3') ac = min(ac,dist[0][i][j] - 1);
	loop(i,m) loop(j,n) if(G[i][j] == '3') bc = min(bc,dist[1][i][j] - 1);
	ans = min(ans,ab + bc);
	ans = min(ans,ab + ac);
	ans = min(ans,bc + ac);
	if(ans >= oo - 10) ans = -1;
	cout << ans << endl;

	return 0;
}
