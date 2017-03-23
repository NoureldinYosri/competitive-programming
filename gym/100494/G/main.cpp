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

char G[100][100];
int dx[] = {0,-1,0,1},dy[] = {-1,0,1,0};
int m,n;
int vis[100][100];

bool smell(int x,int y){
	loop(i,4){
		int nx = x + dx[i],ny = y + dy[i];
		if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
		if(G[nx][ny] == 'T') return 1;
	}
	return 0;
}

int dfs(int x,int y){
	vis[x][y] = 1;
	if(smell(x,y)) return G[x][y] == 'G';
	int ret = G[x][y] == 'G';
	loop(i,4){
		int nx = x + dx[i],ny = y + dy[i];
		if(nx < 0 || nx >= m || ny < 0 || ny >= n || vis[nx][ny] || G[nx][ny] == '#') continue;
		ret += dfs(nx,ny);
	}
	return ret;
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,m) scanf("%s",G[i]);
	loop(i,m) loop(j,n) if(G[i][j] == 'P') printf("%d\n",dfs(i,j));			
	return 0;
}
