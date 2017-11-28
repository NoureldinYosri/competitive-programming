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


const int MAX = 100*1000 + 10,MAXLG = 20;
vi E[MAX];
int fr[MAX],to[MAX],weight[MAX];
int dfs_in[MAX],dfs_out[MAX],dfs_time;
int depth[MAX],P[MAX][MAXLG],n;
int siz[MAX],pref_child[MAX],to_pref_child[MAX],euler[MAX];
int heavy_id[MAX],heavy_siz[MAX],heavy_head[MAX],heavy_cnt;
ll ST[MAX << 2],pref[MAX];
int LA[MAX << 2];


void dfs(int u,int p){
	depth[u] = depth[p] + 1;
	P[u][0] = p;
	loop(i,MAXLG-1) P[u][i + 1] = P[P[u][i]][i];
	siz[u] = 1;
	pref_child[u] = -1;
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v != p) {
			dfs(v,u);
			siz[u] += siz[v];
			if(pref_child[u] == -1 || siz[v] > siz[pref_child[u]]){
				pref_child[u] = v;
				to_pref_child[u] = weight[e];
			}
		}
	}
}

struct cmp{
public:
	bool operator () (const int & a,const int & b){
		return dfs_in[a] < dfs_in[b];
	}
};
set<int,cmp> S;

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


void hld(int u,int p,int w){
	dfs_in[u] = dfs_time;
	euler[dfs_time] = w;
	dfs_time++;

	heavy_id[u] = heavy_cnt;
	if(!heavy_siz[heavy_cnt]) heavy_head[heavy_cnt] = u;
	heavy_siz[heavy_cnt]++;

	if(pref_child[u] != -1) hld(pref_child[u],u,to_pref_child[u]);

	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v != p && v != pref_child[u]) {
			heavy_cnt++;
			hld(v,u,weight[e]);
		}
	}

	dfs_out[u] = dfs_time - 1;
}

void update(int node,int s,int e,int val){
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	LA[node] += val;
	if(LA[node] > 0) ST[node] = pref[e] - (s ? pref[s - 1] : 0);
	else if(LA[node] == 0) {
		if(s == e) ST[node] = 0;
		else ST[node] = ST[left] + ST[right];
	}
	else {
		update(left,s,m,LA[node]);
		update(right,m+1,e,LA[node]);
		ST[node] = ST[left] + ST[right];
		LA[node] = 0;
	}
}

void push(int node,int s,int e){
	if(!LA[node]) return ;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	update(left,s,m,LA[node]);
	update(right,m+1,e,LA[node]);
	LA[node] = 0;
}

void update(int node,int s,int e,int l,int r,int val){
	if(l <= s && e <= r) return update(node,s,e,val);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	push(node,s,e);
	if(r <= m) update(left,s,m,l,r,val);
	else if(m < l)  update(right,m+1,e,l,r,val);
	else update(left,s,m,l,m,val),update(right,m+1,e,m+1,r,val);
	ST[node] = ST[left] + ST[right];
}


void update(int u,int val){
	while(u){
		int id = heavy_id[u];
		int head = heavy_head[id];
		update(1,0,n-1,dfs_in[head],dfs_in[u],val);
		u = P[head][0];
	}
}

ll query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST[node];
	push(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	return query(left,s,m,l,m) + query(right,m+1,e,m+1,r);
}

ll query(int u){
	ll ret = 0;
	while(u){
		int id = heavy_id[u];
		int head = heavy_head[id];
		ret += query(1,0,n-1,dfs_in[head],dfs_in[u]);
		u = P[head][0];
	}
	return ret;
}

ll get_ans(){
	if(S.empty()) return 0;
	ll ret = ST[1];
	int p = lca(*S.begin(),*S.rbegin());
	ret -= query(p);
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(e,n-1){
		scanf("%d %d %d",fr + e,to + e,weight + e);
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
	}
	dfs(1,0);
	hld(1,0,0);
	dfs_out[0] = n;
	loop(e,n-1) {
		if(depth[fr[e]] > depth[to[e]]) swap(fr[e],to[e]);
	}
	loop(i,n) pref[i] = euler[i] + (i ? pref[i - 1] : 0);

	int m; scanf("%d",&m);
	while(m--){
		char type; scanf(" %c",&type);
		if(type == '?') printf("%lld\n",get_ans());
		else {
			int u; scanf("%d",&u);
			if(type == '+') {
				update(u,1);
				S.insert(u);
			}
			else {
				update(u,-1);
				S.erase(u);
			}
		}
	}
	return 0;
}
