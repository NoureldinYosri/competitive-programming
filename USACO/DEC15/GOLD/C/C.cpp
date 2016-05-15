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

#define red 0
#define pink 1
#define orange 2
#define blue 3
#define purple 4
typedef pair<pi,pi> state;
typedef priority_queue<state,vector<state >,greater<state> > pq;

int m,n;
int G[1100][1100];
int D[1100][1100][2];
int dx[] = {-1,1,0,0},dy[] = {0,0,-1,1};

inline void add(int nx,int ny,int nsmell,int x,int y,int smell,int offset,pq & q){
	if(G[nx][ny] == orange) nsmell = 1;	
	if(D[nx][ny][nsmell] > D[x][y][smell] + offset){
		D[nx][ny][nsmell] = D[x][y][smell] + offset;
		q.push(mp(mp(D[nx][ny][nsmell],nsmell),mp(nx,ny)));
	}
}


int dijkstra(){
	if(G[0][0] == red) return -1;
	loop(i,m) loop(j,n) loop(k,2) D[i][j][k] = 1 << 29;
	pq q;
	q.push(mp(mp(0,0),mp(0,0))); D[0][0][0] = 0;
	while(!q.empty()){
		int x = q.top().yy.xx,y = q.top().yy.yy,smell = q.top().xx.yy,w = q.top().xx.xx; q.pop();
		if(x == m - 1 && y == n - 1) return D[x][y][smell];
		//cerr << x << " " << y << " " << smell << " " << D[x][y][smell]  << " " << w << endl;
		if(D[x][y][smell] < w) continue;
		loop(i,4){
			int nx = x + dx[i],ny = y + dy[i];
			if(nx < 0 || nx == m || ny < 0 || ny == n) continue;
			if(G[nx][ny] == red) continue;
			if(G[nx][ny] == pink) add(nx,ny,smell,x,y,smell,1,q);
			if(G[nx][ny] == orange) add(nx,ny,1,x,y,smell,1,q);
			if(G[nx][ny] == blue){
				if(smell) add(nx,ny,1,x,y,1,1,q);
			}
			if(G[nx][ny] == purple){
				int offset = 1;
				while(G[nx][ny] == purple){
					int tx = nx + dx[i],ty = ny + dy[i];
					if(tx < 0 || tx == m || ty < 0 || ty == n) break;
					if(G[tx][ty] == red) break;
					if(G[tx][ty] == blue && !smell) break;
					nx = tx;
					ny = ty;
					offset++;
				}
				add(nx,ny,smell,x,y,smell,offset,q);
			}
		}
	}
	return -1;
}

int main(){
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
  	scanf("%d %d",&m,&n);
	loop(i,m)loop(j,n) scanf("%d",&G[i][j]);
	printf("%d\n",dijkstra());	
	return 0;
}
