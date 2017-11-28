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

const int MAX = 500*1000 + 10,MAXLG = 20;
vi E[MAX];
int fr[MAX],to[MAX],C[MAX],ord[MAX],n,m;
int id[MAX],W[MAX];
int siz[MAX],depth[MAX],dfs_in[MAX],dfs_out[MAX],dfs_time;
int parent[MAX],pref_child[MAX],heavyID[MAX],head[MAX],hsiz[MAX],hcnt,prefC[MAX];
int qE[MAX],q;
vi ST[MAX*4];

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}

bool join(int a,int b) {
	a = find(a),b = find(b);
	if(a == b) return 0;
	if(W[a] < W[b]) swap(a,b);
	id[b] = a;
	W[a] += W[b];
	return 1;
}


void dfs(int u,int p) {
	siz[u] = 1;
	pref_child[u] = 0;
	depth[u] = depth[p] + 1;
	parent[u] = p;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		dfs(v,u);
		siz[u] += siz[v];
		if(siz[v] > siz[pref_child[u]])
			pref_child[u] = v,prefC[u] = C[e];
	}
}


void hld(int u,int p,int c) {
	dfs_in[u] = dfs_time;
	ord[dfs_time++] = c;

	heavyID[u] = hcnt;
	if(!hsiz[hcnt]) head[hcnt] = u;
	hsiz[hcnt]++;

	if(pref_child[u]) hld(pref_child[u],u,prefC[u]);

	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p || v == pref_child[u]) continue;
		hcnt++;
		hld(v,u,C[e]);
	}

	dfs_out[u] = dfs_time-1;
}

void build(int node,int s,int e) {
	for(int k = s;k <= e;k++)
		ST[node].pb(ord[k]);
	sort(all(ST[node]));
	ST[node].pb(INT_MAX);
	if(s == e) return;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
}

pi upperBound(int node,int s,int e,int l,int r,int v) {
	if(l <= s && e <= r) {
		int x = *upper_bound(all(ST[node]),v);
		auto q = equal_range(all(ST[node]),x);
		int c = q.yy - q.xx;
		return mp(x,c);
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return upperBound(left,s,m,l,r,v);
	if(m < l) return upperBound(right,m+1,e,l,r,v);
	auto p = upperBound(left,s,m,l,m,v),q = upperBound(right,m+1,e,m+1,r,v);
	if(p.xx == q.xx) return mp(p.xx,p.yy + q.yy);
	if(p.xx < q.xx) return p;
	else return q;
}


pi upperBound(int u,int v,int val) {
	int x = INT_MAX,cnt = 0;
	while(heavyID[u] != heavyID[v]) {
		if(heavyID[u] > heavyID[v]) swap(u,v);
		int t = head[heavyID[v]];

		auto p = upperBound(1,0,n-1,dfs_in[t],dfs_in[v],val);
		if(p.xx == x) cnt += p.yy;
		else if(p.xx < x) x = p.xx,cnt = p.yy;

		v = parent[t];
	}
	if(depth[u] > depth[v]) swap(u,v);
	if(u != v) {
		auto p = upperBound(1,0,n-1,dfs_in[u]+1,dfs_in[v],val);
		if(p.xx == x) cnt += p.yy;
		else if(p.xx < x) x = p.xx,cnt = p.yy;
	}
	return mp(x,cnt);
}

void preprocess(){
	sort(ord,ord + m,[](const int & a,const int & b) {
		return C[a] < C[b];
	});
	range(i,1,n) id[i] = i,W[i] = 1;
	loop(i,m){
		int e = ord[i];
		if(join(fr[e],to[e])) {
			E[fr[e]].pb(e);
			E[to[e]].pb(e);
		}
	}
	dfs(1,0);
	hld(1,0,0);
	assert(dfs_time == n);
	build(1,0,n-1);
}




int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	loop(e,m) {
		scanf("%d %d %d",fr + e,to + e,C + e);
		ord[e] = e;
	}
	preprocess();
	int Q; scanf("%d",&Q);
	while(Q--) {
		scanf("%d",&q);
		loop(i,q) {
			int e;
			scanf("%d",&e);
			--e;
			qE[i] = e;
		}
		sort(qE,qE + q,[](const int & a,const int & b) {
			return C[a] < C[b];
		});
		bool y = 1;
		map<int,int> M;
		loop(i,q) {
			int e = qE[i];
			int u = fr[e],v = to[e],w = C[e] - 1;
			while(1) {
				cerr << u << " " << v << " search for " << w << endl;
				auto p = upperBound(u,v,w);
				cerr << "for " << w << " got " << p.xx << " " << p.yy << endl;
				if(M.find(p.xx) == M.end()) {
					M[p.xx] = p.yy;
					break;
				}
				if(M[p.xx]) break;
				++w;
			}
			auto p = M.upper_bound(w);
			if(p->xx == INT_MAX) {
				y = 0;
				break;
			}
			assert(M[p->xx] > 0);
			M[p->xx]--;
		}
		puts(y ? "YES" : "NO");
		break;
	}
	return 0;
}
