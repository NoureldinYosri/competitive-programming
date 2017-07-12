#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
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
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
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

bool vis[500][500];
int best[500][500],G[500][500],R,C;
int dx [] = {-1,0,1,0},dy[]  = {0,-1,0,1};

void solve(){
	memset(vis,0,sizeof vis);
	PQ<pair<int,pi> > pq;
	loop(i,R) loop(j,C) {
		best[i][j] = -1;
		pq.push(mp(G[i][j],mp(i,j)));
	}
	while(!pq.empty()){
		int x = pq.top().yy.xx,y = pq.top().yy.yy,val = pq.top().xx;
		pq.pop();
		if(vis[x][y] || !val) continue;
		best[x][y] = val;
		vis[x][y] = 1;
		loop(i,4){
			int nx = x + dx[i],ny = y + dy[i];
			if(nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
			if(vis[nx][ny]) continue;
			if(best[nx][ny] >= val - 1) continue;
			best[nx][ny] = val - 1;
			pq.push(mp(val-1,mp(nx,ny)));
		}
	}
	int ans = 0;
	loop(i,R) loop(j,C) ans += best[i][j] == -1;
	printf("%d\n",ans);
}

int main(){
	freopen("interesting.in", "r", stdin);
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d",&R,&C);
		loop(i,R) loop(j,C) scanf("%d",&G[i][j]);
		solve();

	}

	return 0;
}
