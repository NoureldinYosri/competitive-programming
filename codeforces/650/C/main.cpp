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

const int MAX = 1 << 20;
int row[MAX],col[MAX];
pair<int,pi> E[MAX];
vector<vi> G;
int m,n;
int cur_row[MAX],cur_col[MAX];
vi adj[2*MAX];
int vis[2*MAX];

void dfs_query(int cur,int & val){
	if(cur < m) val = max(val,row[cur] + 1);
	else val = max(val,col[cur - m] + 1);
	vis[cur] = 1;
	for(int x : adj[cur]) if(!vis[x]) dfs_query(x,val);
}

void dfs_set(int cur,int val){
	if(cur < m) row[cur] = val;
	else col[cur - m] = val;
	vis[cur] = 2;
	for(int x : adj[cur]) if(vis[x] != 2) dfs_set(x,val);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&m,&n);
	G = vector<vi>(m,vi(n,0));
	int N = 0;
	loop(i,m) loop(j,n){
		int x; scanf("%d",&x);
		E[N++] = mp(x,mp(i,j));
	}
	sort(E,E + N);
	for(int i = 0;i < N;){
		int j = i;
		while(j < N && E[i].xx == E[j].xx) {
			int r = E[j].yy.xx,c = E[j].yy.yy;
			adj[r].clear();
			adj[c + m].clear();
			j++;
		}
		for(int t = i;t < j;t++){
			int r = E[t].yy.xx,c = E[t].yy.yy;
			vis[r] = 0;
			vis[c + m] = 0;
			adj[r].pb(c + m);
			adj[c + m].pb(r);
		}
		for(int t = i;t < j;t++){
			int r = E[t].yy.xx,c = E[t].yy.yy;
			assert(!(vis[r] ^ vis[c + m]));
			if(vis[r]) continue;
			int val = 0;
			dfs_query(r,val);
			dfs_set(r,val);
		}
		for(;i < j;i++) {
			int r = E[i].yy.xx,c = E[i].yy.yy;
			assert(cur_row[r] == cur_col[c]);
			G[r][c] = row[r];
		}
	}
	loop(i,m) loop(j,n) printf("%d%c",G[i][j]," \n"[j==n-1]);
	return 0;
}
