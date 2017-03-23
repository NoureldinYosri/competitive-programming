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

int dist[1000][1000];
char G[1000][1000];
int dx [] = {0,0,-1,1},dy[] = {1,-1,0,0};
int main(){
	int m,n; cin >> m >> n;
	loop(i,m) cin >> G[i];
	memset(dist,-1,sizeof dist);
	int x,y; cin >> x >> y; x--,y--;
	dist[x][y] = 0;
	queue<pi> q; q.push(mp(x,y));
	int ans = 0;
	while(!q.empty()){
		x = q.front().xx,y = q.front().yy; q.pop();
		loop(i,4){
			int nx = x + dx[i],ny = y + dy[i];
			if(nx < 0 || nx >= m || ny < 0 || ny >= n || dist[nx][ny] != -1 || G[nx][ny] == '#') continue;
			ans = dist[nx][ny] = dist[x][y] + 1;
			q.push(mp(nx,ny));
		}
	}	
	loop(i,m) loop(j,n) if(G[i][j] == '.' && dist[i][j] == -1) ans = -1;
	cout << ans << endl;
	return 0;
}
