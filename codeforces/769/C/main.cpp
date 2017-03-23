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

const int MAX = 1111;
bool vis[MAX][MAX];
char name [] = "DLRU";
int dx [] = {1,0,0,-1},dy [] = {0,-1,1,0};
char G[MAX][MAX];
int m,n,k;
int len[MAX][MAX];
int to[MAX][MAX],inTime[MAX][MAX];
pi P[MAX][MAX];

int main(){
	scanf("%d %d %d",&m,&n,&k);
	if(k & 1){
		puts("IMPOSSIBLE");
		return 0;
	}	
	int sx = -1,sy;
	loop(i,m){
		scanf("%s",G[i]);
		loop(j,n) {
			if(G[i][j] == 'X') sx = i,sy = j;
			to[i][j] = 255;
		}
	}
	assert(sx != -1);
	typedef pair<int,pi> state; 
	PQ< state ,vector<state>,greater<state> > pq;
	pq.push(mp(0,mp(sx,sy)));
	P[sx][sy] = mp(-1,-1);
	for(int t = 0;!pq.empty();t++) {
		int x = pq.top().yy.xx,y = pq.top().yy.yy; pq.pop();
		if(vis[x][y]) continue;
//		cerr << x << " " << y << " " << name[to[x][y]] << endl;		
		vis[x][y] = 1;
		inTime[x][y] = t;
		for(int i = 0;i < 4;i++){
			int nx = x + dx[i],ny = y + dy[i];
			if(nx < 0 || nx >= m || ny < 0 || ny >= n || vis[nx][ny] || G[nx][ny] == '*' || to[nx][ny] != 255) continue;
			P[nx][ny] = mp(x,y);
			len[nx][ny] = len[x][y] + 1;
			to[nx][ny] = i;
			pq.push(mp((i << 21) | t,mp(nx,ny)));
		}
	}
	int ex = -1,ey;
	for(int i = 0;i < m;i++){
		for(int j = 0;j < n;j++){
			if(len[i][j] && k%(2*len[i][j]) == 0){
				if(ex == -1) ex = i,ey = j;
				else if(len[i][j] > len[ex][ey]) ex = i,ey = j;
				else if(len[i][j] == len[ex][ey] && inTime[i][j] < inTime[ex][ey]) ex = i,ey = j;
			}
		}
	}
	if(ex == -1){
		puts("IMPOSSIBLE");
		return 0;
	}	
	string s;
	while(ex != sx || ey != sy){
		s.pb(name[to[ex][ey]]);
		pi tmp = P[ex][ey];
		ex = tmp.xx;
		ey = tmp.yy;
	}
	reverse(all(s));
	for(int i = sz(s) - 1;i >= 0;i--){
		if(s[i] == 'L') s.pb('R');
		else if(s[i] == 'R') s.pb('L');
		else if(s[i] == 'U') s.pb('D');
		else s.pb('U');
	}
	int L = sz(s);
	loop(i,k/L - 1) for(int j = 0;j < L;j++) s.pb(s[j]); 
	cerr << s << endl;
	cout << s << endl;	
	return 0;
}
