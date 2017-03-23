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

const int MAX = 2010,MAXD = MAX*MAX;

char G[MAX][MAX];
int vis[MAX][MAX];
int m,n;

int cnt(int x,int y){
	if(x < 0 || y < 0) return 0;
	if(x+1==m || y+1==n) return 0;
	return (G[x][y] == '*') + (G[x][y + 1] == '*') + (G[x+1][y] == '*') + (G[x+1][y+1] == '*');
}

bool cond(int x,int y){
	if(cnt(x-1,y-1) == 1) return 1;
	if(cnt(x-1,y) == 1) return 1;
	if(cnt(x,y-1) == 1) return 1;
	if(cnt(x,y) == 1) return 1;
	return 0;
}

int main(){
	scanf("%d %d",&m,&n);
	loop(i,m) scanf("%s",G [i]);
	queue<pi> q;
	loop(i,m) loop(j,n) if(G[i][j] == '*' && cond(i,j)) {
		q.push(mp(i,j));
		vis[i][j] = 1;
	}
	while(!q.empty()){
		int x = q.front().xx,y = q.front().yy; q.pop();
		G[x][y] = '.';
		range(dx,-1,1) range(dy,-1,1) if(abs(dx) + abs(dy)) {
			int nx = x + dx,ny = y + dy;
			if(nx < 0 || ny < 0 || nx >= m || ny >= n || G[nx][ny] == '.' || vis[nx][ny] || !cond(nx,ny)) continue;
			q.push(mp(nx,ny));
			vis[nx][ny] = 1;
		}
	}

	loop(i,m) {
		puts(G[i]);
//		cerr << G[i] << endl;
	}
	return 0;
}
