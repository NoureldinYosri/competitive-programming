/*
 * #include <bits/stdc++.h>
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
#define popcnt(x) __builtin_popcount(x)
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

const int MAX = 55;
char G[MAX][MAX];
int m,n;
int vis[MAX][MAX];
int dx [] = {0,-1,0,1},dy [] = {-1,0,1,0};
queue<pi> q;

void dfs(int x,int y,int pass){
	q.push(mp(x,y));
	vis[x][y] = 1;
	for(int k = 0;k < 4;k++){
		int nx = x + dx[k],ny = y + dy[k];
		if(nx < 0 || nx >= m || ny < 0 || ny >= n || vis[nx][ny] || G[nx][ny] == '#') continue;
		if(!pass && G[nx][ny] == '?') continue;
		dfs(nx,ny,pass);
	}
}

int main(){
	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	scanf("%d %d",&m,&n);
	loop(i,m) scanf("%s",G[i]);
	loop(i,m) loop(j,n) if(G[i][j] == '.') {
		dfs(i,j,1);
		break;
	}
	loop(i,m) loop(j,n) if(G[i][j] == '.' && !vis[i][j]) {
		puts("Impossible");
		return 0;
	}
	loop(i,m) loop(j,n) if(G[i][j] == '?' && !vis[i][j]) G[i][j] = '#';
	memset(vis,0,sizeof vis);
	loop(i,m) loop(j,n)
	return 0;
}
*/
