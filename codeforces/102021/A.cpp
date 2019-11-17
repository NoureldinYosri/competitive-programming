#ifdef ACTIVE
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;


const int MAX = 2000 + 10,MAXN = MAX*MAX;
int H,W;
int dx [] = {0,-1,0,1},dy [] = {-1,0,1,0};
char G[MAX][MAX];




const int MAXL = 1 << 20;
char buffer[MAXL];
int name[MAX][MAX];
vi adj[MAXN];

const int MAXLG = 20;
int dfs_in[MAXN],dfs_out[MAXN],dfs_time;
int depth[MAXN];
int P[MAXN][MAXLG];

void dfs(int u,int p) {
	dfs_in[u] = dfs_time++;
	P[u][0] = p;
	depth[u] = depth[p] + 1;
	loop(k,MAXLG-1) P[u][k+1] = P[P[u][k]][k];
	assert(u);
	for(int v : adj[u]) if(v != p) dfs(v,u);
	dfs_out[u] = dfs_time - 1;
}

bool inSubTree(int a,int b){
	return dfs_in[b] <= dfs_in[a] && dfs_in[a] <= dfs_out[b];
}

int lca(int a,int b){
	if(depth[a] > depth[b]) swap(a,b);
	if(inSubTree(b,a)) return a;
	int k = MAXLG - 1;
	while(a != b){
		if(depth[a] > depth[b]) swap(a,b);
		while(k && inSubTree(a,P[b][k])) k--;
		b = P[b][k];
	}
	return a;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	fgets(buffer,MAXL,stdin);
	sscanf(buffer,"%d %d",&H,&W);
	loop(r,H+1){
		fgets(buffer,MAXL,stdin);
		strncpy(G[r],buffer,2*W+1);
		G[r][2*W+1] = 0;
//		printf("\"%s\"\n",G[r]);
	}
	for(int r = 1,m = 0;r <= H;r++)
		for(int c = 1;c <= W;c++) {
			name[r][c] = ++m;
		}
	for(int r = 1;r <= H;r++) {
		for(int c = 1;c <= W;c++) {
			int mc = 2*c-1;
			int left = G[r][mc-1] != '|',right = G[r][mc+1] != '|';
			int up = G[r-1][mc] != '_';
			int down = G[r][mc] != '_';
			int go[] = {left,up,right,down};
			loop(k,4) if(go[k]) {
				int x = r + dx[k],y = c + dy[k];
//				cout << r << " " << c << " " << k << " " << x << " " << y << " \"" << G[r][2*c-1] << "\""<< endl;
				assert(x >= 1 && x <= H && y >= 1 && y <= W);
				assert(name[x][y]);
				assert(name[r][c]);
				adj[name[r][c]].push_back(name[x][y]);
			}
		}
	}


//	for(int u = 1;u <= H*W;u++)
//		for(int v : adj[u]) if(u < v)
//			cout << u << " " << v << endl;

	dfs(1,0);
	dfs_out[0] = 1 << 20;
	int Q; scanf("%d",&Q);
	int x,y; scanf("%d %d",&x,&y);
	int u = name[x][y];

	Q--;
	ll ans = 0;
	while(Q-- > 0) {
		scanf("%d %d",&x,&y);
		int v = name[x][y];
		ans += depth[u] + depth[v] - 2*depth[lca(u,v)];
		u = v;
	}
	printf("%lld\n",ans);
	return 0;
}
#endif
