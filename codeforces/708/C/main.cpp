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

const int MAX = 400*1000 + 10;
vi G[MAX];
int siz[MAX],n;
int can[MAX],biggest_child[MAX];
int ST[MAX*4];
int dfs_in[MAX],dfs_out[MAX],dfs_time,euler[MAX];


int dfs(int u,int p){
	dfs_in[u] = dfs_time++;
	siz[u] = 1;
	for(int v : G[u]) if(v != p) {
		siz[u] += dfs(v,u);
		if(siz[v] > siz[biggest_child[u]] )
			biggest_child[u] = v;
	}
	euler[dfs_in[u]] = siz[u];
	dfs_out[u] = dfs_time-1;
	return siz[u];
}

void build(int node,int s,int e){
	if(s == e) {
		ST[node] = (euler[s] > n/2) ? INT_MIN : euler[s];
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
	ST[node] = max(ST[left],ST[right]);
}

int query(int node,int s,int e,int l,int r,int val) {
	if(l <= s && e <= r) {
		if(ST[node] >= val) return ST[node];
		else return INT_MIN;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r,val);
	if(m < l) return query(right,m+1,e,l,r,val);
	int x = query(left,s,m,l,m,val);
	if(x == INT_MIN) x = query(right,m+1,e,m+1,r,val);
	return x;
}

void update(int node,int s,int e,int p,int val){
	if(s == e) {
		ST[node] = (val > n/2) ? -1 : val;
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) update(left,s,m,p,val);
	else update(right,m+1,e,p,val);
	ST[node] = max(ST[left],ST[right]);
}

void solve(int u,int p){
	int up = n-siz[u];
	int ctr = up > n/2;
	for(int v : G[u]) if(v != p) ctr += siz[v] > n/2;
	if(ctr > 1) can[u] = 0;
	else if(ctr == 1) {
		can[u] = 2;
		if(up > n/2) {
			int x = INT_MIN;
			if(dfs_in[u]) x = max(x,query(1,0,n-1,0,dfs_in[u]-1,up - n/2));
			if(dfs_out[u] < n-1) x = max(x,query(1,0,n-1,dfs_out[u]+1,n-1,up - n/2));
			can[u] = x != INT_MIN;
		}
		else {
			int t = biggest_child[u];
			int x = query(1,0,n-1,dfs_in[t],dfs_out[t],siz[t] - n/2);
			can[u] = x != INT_MIN;
		}
	}
	else can[u] = 1;

	for(int v : G[u]) if(v != p) {
		update(1,0,n-1,dfs_in[u],n - siz[v]);
		solve(v,u);
	}
	update(1,0,n-1,dfs_in[u],siz[u]);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1,0);
	build(1,0,n-1);
	solve(1,0);
	range(i,1,n) {
		putchar(can[i] + '0');
		if(i == n) puts("");
		else putchar(' ');
	}
	return 0;
}
