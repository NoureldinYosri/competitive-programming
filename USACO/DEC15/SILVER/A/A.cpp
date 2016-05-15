#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

int dx [] = {-1,1,0,0},dy [] = {0,0,-1,1};
vector<pi> Adj[110][110];
int status[110][110];
int V[110][110];

int main(){
	freopen("lightson.in","r",stdin);
	freopen("lightson.out","w",stdout);
  	int n,m,x,y,a,b;
	cin >> n >> m;
	loop(i,m){
		cin >> x >> y >> a >> b;
		Adj[x][y].pb(mp(a,b));
	}
	queue<pi> q,oq;
	q.push(mp(1,1));
	V[1][1] = 1;
	status[1][1] = 3;
	int ans = 0;
	while(!q.empty()){
		int x = q.front().xx,y = q.front().yy; q.pop();
		for(auto p : Adj[x][y])	{
			status[p.xx][p.yy] |= 1;
			if((status[p.xx][p.yy] & 2) && !V[p.xx][p.yy]){
				V[p.xx][p.yy] = 1;
				q.push(mp(p.xx,p.yy));
			}
		}
		loop(i,4){
			int nx = x + dx[i],ny = y + dy[i];
			if(nx <= 0 || nx > n || ny <= 0 || ny > n) continue;
			if(!V[nx][ny]){
				if(status[nx][ny] & 1){
					V[nx][ny] = 1;
					q.push(mp(nx,ny));
				}
				else status[nx][ny] |= 2;
			}
		}
	}
	loop(i,n + 1) loop(j,n + 1) ans += status[i][j] & 1;
	cout << ans << endl;
	return 0;
}
