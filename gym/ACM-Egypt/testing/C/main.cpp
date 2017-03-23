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

const int MAX = 1000;
const ll SMAXH = 1000'000'000;
const ll MAXH = SMAXH*SMAXH;
int m,n;
int r,c,x,y; 
ll H[MAX][MAX];
int dx[] = {0,-1,0,1},dy[] = {-1,0,1,0};
int vis[MAX][MAX];

bool can(ll h){
	if(H[r][c] <= h) return 0;
	queue<pi> q; q.push(mp(r,c));
	memset(vis,0,sizeof vis); vis[r][c] = 1;
	while(!q.empty()){ 
		int ux = q.front().xx,uy = q.front().yy; q.pop();
		loop(i,4){
			int vx = ux + dx[i],vy = uy + dy[i];
			if(vx < 0 || vx >= m || vy < 0 || vy >= n) continue;
			if(vis[vx][vy] || H[vx][vy] <= h) continue;
			q.push(mp(vx,vy));
			vis[vx][vy] = 1;
		}
	}
	return vis[x][y];
}

int main(){
	scanf("%d %d",&m,&n);
	assert(1 <= m && m <= MAX);
	assert(1 <= n && n <= MAX);
	scanf("%d %d %d %d",&r,&c,&x,&y);
	assert(1 <= r && r <= m);
	assert(1 <= x && x <= m);
	assert(1 <= c && c <= n);
	assert(1 <= y && y <= n);
	r--,c--,x--,y--;
	loop(i,m) loop(j,n){
		scanf("%lld",&H[i][j]);
		assert(1 <= H[i][j] && H[i][j] <= MAXH);
	}
	assert(can(1));
	ll s = 1,e = MAXH;
	while(s < e){		
		ll m = s + (e - s + 1)/2;
		if(can(m)) s = m;
		else e = m - 1;
	}
	cerr << s << endl;
	
	return 0;
}
