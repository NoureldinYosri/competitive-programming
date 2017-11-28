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

const int MAX = 200*1000 + 10;
vi G[MAX];
int ord[MAX],dfs_in[MAX],dfs_out[MAX],dfs_time;
int BIT[MAX],n;
int color[MAX];
int ST[MAX * 4][2];
int LA[MAX * 4];

void build(int node,int s,int e) {
	if(s == e) ST[node][color[ord[s]]]++;
	else {
		int m = (s + e) >> 1,left = node << 1,right = left | 1;
		build(left,s,m);
		build(right,m+1,e);
		loop(i,2) ST[node][i] = ST[left][i] + ST[right][i];
	}
}

void update(int node) {
	swap(ST[node][0],ST[node][1]);
	LA[node] ^= 1;
}

void push(int node) {
	if(!LA[node]) return;
	int left = node << 1,right = left | 1;
	update(left);
	update(right);
	LA[node] = 0;
}

void update(int node,int s,int e,int l,int r) {
	if(l <= s && e <= r) return update(node);
	push(node);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) update(left,s,m,l,r);
	else if(m < l) update(right,m+1,e,l,r);
	else update(left,s,m,l,m),update(right,m+1,e,m+1,r);
	loop(i,2) ST[node][i] = ST[left][i] + ST[right][i];
}

int query(int node,int s,int e,int l,int r) {
	if(l <= s && e <= r) return ST[node][1];
	push(node);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	return query(left,s,m,l,m) + query(right,m+1,e,m+1,r);
}


void dfs(int u) {
	dfs_in[u] = ++dfs_time;
	ord[dfs_time] = u;
	for(int v : G[u])
		dfs(v);
	dfs_out[u] = dfs_time;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(u,2,n) {
		int p; scanf("%d",&p);
		G[p].pb(u);
	}
	range(i,1,n) scanf("%d",color + i);
	dfs(1);
	build(1,1,n);
	int m; scanf("%d",&m);
	while(m--) {
		char s[10];
		int v;
		scanf("%s %d",s,&v);
		if(s[0] == 'g') printf("%d\n",query(1,1,n,dfs_in[v],dfs_out[v]));
		else update(1,1,n,dfs_in[v],dfs_out[v]);
	}
	return 0;
}
