#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

int n,m,p;
int G[310][310];
int dp[2][310*310];
int head[310*310 + 1];
int nxt[310*310 ];
int cnt[310*310 + 1];
int D[310][310];
int dx[] = {1,-1,0,0},dy [] = {0,0,-1,1};

void dijkstra(int l,int o){
	fill(&D[0][0],&D[310][310],1 << 29);
	PQ<pi,vector<pi>,greater<pi> > pq;
	for(int u = head[l], i = 0; u != -1 ;u = nxt[u],i++) 
		pq.push(mp(dp[o][i],u)),D[u/n][u%n] = dp[o][i];
	while(!pq.empty()){
		int u = pq.top().yy,d = pq.top().xx; 	pq.pop(); 
		int x = u/n,y = u%n;
		if(d > D[x][y]) continue;
		loop(i,4){
			int nx = x + dx[i],ny = y + dy[i];
			if(nx < 0 || nx == m || ny < 0 || ny == n) continue;
			if(D[x][y] + 1 >= D[nx][ny]) continue;
			D[nx][ny] = D[x][y] + 1;
			pq.push(mp(D[nx][ny],nx*n + ny));
		}
	}
	for(int u = head[l + 1],i = 0; u != -1 ;u = nxt[u],i++) {
		int x = u/n,y = u%n;
		dp[o^1][i] = D[x][y];
	}
}

int main(){
	fill(head,head + 310*310,-1);
	scanf("%d %d %d",&m,&n,&p);
	loop(i,m) loop(j,n) {
		scanf("%d",&G[i][j]);
		nxt[i*n + j] = head[G[i][j]];
		head[G[i][j]] = i*n + j;
		cnt[G[i][j]]++;
	}
	int one = 1,other = 0;
	range(k,1,p){
		one ^= 1,other ^= 1;
		if(cnt[k - 1]*1LL*cnt[k] >= n*m) {
			dijkstra(k - 1,other);
			continue;
		}
		for(int i = 0,u = head[k]; u != -1; u = nxt[u],i++){
			int x = u/n,y = u%n;
			if(k == 1) dp[one][i] = x + y;
			else{
				dp[one][i] = INT_MAX;
				for(int v = head[k - 1],j = 0; v != -1; v = nxt[v],j++){
					int ox = v/n,oy = v%n;
					dp[one][i] = min(dp[one][i],dp[other][j] + abs(x - ox) + abs(y - oy));
				}		
			}	
		}
	}
	cout << dp[one][0] << endl;
	return 0;
}
